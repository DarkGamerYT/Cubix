#include "ServerInstance.hpp"

#include "commands/standard/StopCommand.hpp"
#include "commands/standard/TestCommand.hpp"
#include "commands/standard/GiveCommand.hpp"

ServerInstance::ServerInstance()
{
    this->mLevel = std::make_shared<ServerLevel>(this);
};
ServerInstance::~ServerInstance()
{
    this->shutdown();
    if (this->mServerThread.joinable())
    {
        this->mServerThread.join();
    };
};

void ServerInstance::initializeServer(
    const LevelSettings& levelSettings,
    const PlayerTickPolicy tickPolicy,
    const ConnectionDefinition& connectionDefintion,
    const bool requireOnlineAuthentication,
    const TransportLayer transportLayer
) {
    BlockStateRegistry::initialize();
    BlockRegistry::initialize();
    ItemRegistry::initialize();
    ItemGroupRegistry::initialize();

    this->initializeCommands();

    this->mLevel->initialize(levelSettings);

    this->mNetwork = std::make_shared<ServerNetworkHandler>(this->mLevel, this, connectionDefintion, requireOnlineAuthentication);
    this->mNetwork->setTransportLayer(transportLayer);

    this->mPlayerTickPolicy = tickPolicy;
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
    if (this->mInstanceState != InstanceState::Running)
        return;

    std::vector<std::future<void>> tasks;

    tasks.emplace_back(std::async(std::launch::async, &ServerLevel::tick, this->mLevel.get(), nTick));
    tasks.emplace_back(std::async(std::launch::async, &ServerNetworkHandler::onTick, this->mNetwork.get(), nTick));

    // Player ticks
    if ((this->mPlayerTickPolicy == PlayerTickPolicy::THROTTLED && nTick % 2 == 0)
        || this->mPlayerTickPolicy == PlayerTickPolicy::THROTTLED)
    {
        tasks.emplace_back(std::async(std::launch::async, &ServerNetworkHandler::onTickPlayers, this->mNetwork.get(), nTick));
    };

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
    if (this->mInstanceState != InstanceState::Running)
        return;

    Logger::log(Logger::LogLevel::Info, "Shutting down server...");

    this->mInstanceState.store(InstanceState::Stopped);
    this->mInstanceState.notify_all();

    this->mNetwork->shutdown();
};

void ServerInstance::startServerThread()
{
    this->mInstanceState.store(InstanceState::Running);
    this->mInstanceState.notify_all();
    this->mNetwork->initializeNetwork();

    this->mServerThread = std::thread([&](ServerInstance* p_ServerInstance) {
        const int msPerTick = 1000 / p_ServerInstance->mTicksPerSecond;

        int tickCount = 0;
        auto previousTime = std::chrono::high_resolution_clock::now();

        while (p_ServerInstance->mInstanceState == InstanceState::Running)
        {
            constexpr int maxSkipTicks = 5;
            auto currentTime = std::chrono::high_resolution_clock::now();
            int64_t elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();

            while (elapsedTime >= msPerTick && tickCount < maxSkipTicks)
            {
                // Tick the server
                p_ServerInstance->onTick(p_ServerInstance->mCurrentTick);
                p_ServerInstance->mCurrentTick++;

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