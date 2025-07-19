#include "DedicatedServer.hpp"

DedicatedServer::DedicatedServer()
{
    this->initializeLogging();
};

DedicatedServer::~DedicatedServer()
{

};

void DedicatedServer::initializeLogging()
{
    Logger::log(Logger::LogLevel::Info, "Setting up server logging...");
    {
        std::ofstream ofs("cubix.log", std::ios::out | std::ios::trunc);
        if (ofs.is_open())
            ofs.close();
    };

    Logger::s_File.open("cubix.log", std::ios::app);
    Logger::initialize();
};

void DedicatedServer::start()
{
    Logger::log(Logger::LogLevel::Info, "Starting Server");

    const semver::version& version = SharedConstants::CurrentGameVersion.semver();
    Logger::log(Logger::LogLevel::Info,
        "Version: {} (Protocol: {})", version.str(), SharedConstants::NetworkProtocolVersion);

    const Util::UUID& sessionId = Util::UUID::randomUUID();
    Logger::log(Logger::LogLevel::Info, "Session ID: {}", sessionId.toString());
    Logger::log(Logger::LogLevel::Info, "Build ID: {}", GIT_COMMIT_TIME);
    Logger::log(Logger::LogLevel::Info, "Branch: {}", GIT_BRANCH);
    Logger::log(Logger::LogLevel::Info, "Commit ID: {}", GIT_SHA);
    Logger::log(Logger::LogLevel::Info, "Configuration: {}", BUILD_TYPE);


    const PropertiesSettings propertiesSettings("server.properties");
    if (!propertiesSettings.isPropertiesFileLoaded())
    {
        Logger::log(Logger::LogLevel::Error,
            "Could not load 'server.properties' file. Please check if the base directory includes all the required content.");
        return;
    };

    if (propertiesSettings.useAllowList() && !propertiesSettings.useOnlineAuthentication())
    {
        Logger::log(Logger::LogLevel::Error,
            "Using an allowlist but without online authentication can be dangerous and is not allowed.");
        return;
    };


    const std::string& levelName = propertiesSettings.getLevelName();
    Logger::log(Logger::LogLevel::Info, "Level Name: {}", levelName);

    const auto gameMode = propertiesSettings.getGameMode();
    Logger::log(Logger::LogLevel::Info,
        "GameMode: {} {}", static_cast<int>(gameMode), GameMode::asString(gameMode));

    const auto difficulty = propertiesSettings.getDifficulty();
    Logger::log(Logger::LogLevel::Info,
        "Difficulty: {} {}", static_cast<int>(difficulty), DifficultyUtils::asString(difficulty));

    /*LevelSettings levelSettings;
    levelSettings.setLevelName(levelName);
    levelSettings.parseSeed(propertiesSettings.getLevelSeed());
    levelSettings.setGameType(gameMode);
    levelSettings.setDifficulty(difficulty);*/


    const unsigned short portV4 = propertiesSettings.getServerPort();
    const unsigned short portV6 = propertiesSettings.getServerPortV6();

    // Start server
    m_ServerInstance.initializeServer(propertiesSettings.getPlayerTickPolicy(), {
        propertiesSettings.getServerName(),
        propertiesSettings.getMaxPlayers(),
        { portV4, portV6 },
        propertiesSettings.isServerVisibleToLanDiscovery(),
        propertiesSettings.useOnlineAuthentication(),
    });

    std::thread([](ServerInstance* instance) {
        std::string input;
        while (std::getline(std::cin, input)) {
            if (input.empty())
                continue;

            CommandOutput output{ CommandOutputType::LastOutput };
            CommandOrigin origin{ CommandOriginType::DedicatedServer, instance, Util::UUID::randomUUID(), "" };
            instance->runCommand(input, origin, output);

            CommandOutputMessage commandMessage = output.getMessages().front();
            if (output.getMessages().empty())
                return;

            Logger::log(
                commandMessage.isSuccessful ? Logger::LogLevel::Info : Logger::LogLevel::Error,
                "{}", commandMessage.message);
        };
    }, &m_ServerInstance).detach();

    m_ServerInstance.waitUntil(ServerInstance::InstanceState::Stopped);
};

void DedicatedServer::shutdown()
{
    m_ServerInstance.shutdown();
    Logger::shutdown();
};