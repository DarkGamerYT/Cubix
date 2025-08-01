#include "ServerInstance.hpp"

#include "commands/standard/StopCommand.hpp"
#include "commands/standard/TestCommand.hpp"
#include "commands/standard/GiveCommand.hpp"

ServerInstance::ServerInstance()
{

};
ServerInstance::~ServerInstance()
{
    this->shutdown();
    if (this->m_ServerThread.joinable())
    {
        this->m_ServerThread.join();
    };
};

void ServerInstance::initializeServer(
    const PlayerTickPolicy tickPolicy,
    const ConnectionDefinition& connectionDefintion
) {
    BlockStateRegistry::initialize();
    BlockRegistry::initialize();
    ItemRegistry::initialize();
    ItemGroupRegistry::initialize();

    this->initializeCommands();

    this->m_Network = std::make_shared<ServerNetworkHandler>(this, connectionDefintion);
    this->m_Network->setTransportLayer(TransportLayer::RakNet);

    this->m_PlayerTickPolicy = tickPolicy;
    this->startServerThread();
};

void ServerInstance::initializeCommands()
{
    CommandRegistry::initialize(false);

    CommandRegistry::registerCommand<StopCommand>("stop", CommandPermissionLevel::Any);
    CommandRegistry::registerCommand<TestCommand>("meow", CommandPermissionLevel::Any);
    CommandRegistry::registerCommand<GiveCommand>("give", CommandPermissionLevel::Any);
};

void ServerInstance::onTick(const uint32_t nTick) const
{
    if (this->m_InstanceState != InstanceState::Running)
        return;

    std::vector<std::future<void>> tasks;

    // Logger::log(Logger::LogLevel::Debug, "Current tick: {}", nTick);

    int playerTickInterval = 1;
    if (this->m_PlayerTickPolicy == PlayerTickPolicy::THROTTLED)
        playerTickInterval = 2;

    if (nTick % playerTickInterval == 0)
    {
        // Player ticks
        this->m_Network->onTickPlayers(nTick);
    };

    tasks.emplace_back(std::async(std::launch::async,
        [&] { this->m_Network->onTick(nTick); }));

    for (auto& task : tasks)
    {
        task.wait();
    };
};

void ServerInstance::runCommand(const std::string& command, const CommandOrigin& origin, CommandOutput& output) {
    const std::vector<std::string>& arg = Util::splitString(command, "/ ");

    const auto& commands = CommandRegistry::getAll();
    if (!commands.contains(arg[0]))
    {
        output.error("commands.generic.unknown", { arg[0] });
        return;
    };

    const auto& pCommand = commands.at(arg[0]);
    pCommand->run(origin, output);
};

void ServerInstance::shutdown()
{
    if (this->m_InstanceState != InstanceState::Running)
        return;

    Logger::log(Logger::LogLevel::Info, "Shutting down server...");

    this->m_InstanceState.store(InstanceState::Stopped);
    this->m_InstanceState.notify_all();

    this->m_Network->shutdown();
};

void ServerInstance::startServerThread()
{
    this->m_InstanceState.store(InstanceState::Running);
    this->m_InstanceState.notify_all();
    this->m_Network->initializeNetwork();

    this->m_ServerThread = std::thread([&](ServerInstance* p_ServerInstance) {
        const int msPerTick = 1000 / p_ServerInstance->m_TicksPerSecond;

        int tickCount = 0;
        auto previousTime = std::chrono::high_resolution_clock::now();

        while (p_ServerInstance->m_InstanceState == InstanceState::Running)
        {
            constexpr int maxSkipTicks = 5;
            auto currentTime = std::chrono::high_resolution_clock::now();
            int64_t elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();

            while (elapsedTime >= msPerTick && tickCount < maxSkipTicks)
            {
                // Tick the server
                p_ServerInstance->onTick(p_ServerInstance->m_CurrentTick);
                p_ServerInstance->m_CurrentTick++;

                elapsedTime -= msPerTick;
                previousTime += std::chrono::milliseconds(msPerTick);
                tickCount++;
            };

            tickCount = 0;
            if (elapsedTime < msPerTick)
            {
                const std::chrono::milliseconds& time = std::chrono::milliseconds(msPerTick) - std::chrono::milliseconds(elapsedTime);
                std::this_thread::sleep_for(time);
            };
        };
    }, this);
};