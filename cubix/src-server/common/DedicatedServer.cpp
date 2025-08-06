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


    const PropertiesSettings propertiesSettings{ "server.properties" };
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

    const GameType gameMode = propertiesSettings.getGameMode();
    Logger::log(Logger::LogLevel::Info,
        "GameMode: {} {}", static_cast<int>(gameMode), GameMode::asString(gameMode));

    const Difficulty difficulty = propertiesSettings.getDifficulty();
    Logger::log(Logger::LogLevel::Info,
        "Difficulty: {} {}", static_cast<int>(difficulty), DifficultyUtils::asString(difficulty));

    const LevelSeed64 levelSeed{ propertiesSettings.getLevelSeed() };

    LevelSettings levelSettings{};
    //levelSettings.setLevelName(levelName);
    levelSettings.setSeed(levelSeed);
    levelSettings.setGameType(gameMode);
    levelSettings.setDifficulty(difficulty);
    levelSettings.setDefaultPermissionLevel(propertiesSettings.getDefaultPermissionLevel());


    ConnectionDefinition connectionDefinition;
    connectionDefinition.serverName = propertiesSettings.getServerName();
    connectionDefinition.maxPlayers = propertiesSettings.getMaxPlayers();
    connectionDefinition.serverPorts = { propertiesSettings.getServerPort(), propertiesSettings.getServerPortV6() };
    connectionDefinition.isServerVisibleToLanDiscovery = propertiesSettings.isServerVisibleToLanDiscovery();

    connectionDefinition.compressionType = propertiesSettings.getCompressionAlgorithm();
    connectionDefinition.compressionThreshold = propertiesSettings.getCompressionThreshold();

    // Start server
    mServerInstance.initializeServer(
        levelSettings,
        propertiesSettings.getPlayerTickPolicy(),
        connectionDefinition,
        propertiesSettings.useOnlineAuthentication(),
        propertiesSettings.getTransportLayer());

    std::thread([](ServerInstance* instance) {
        std::string input;
        while (std::getline(std::cin, input)) {
            if (input.empty())
                continue;

            CommandOutput output{ CommandOutputType::LastOutput };
            CommandOrigin origin{ CommandOriginType::DedicatedServer, instance, Util::UUID::randomUUID(), "" };
            instance->runCommand(input, origin, output);

            if (output.getMessages().empty())
                return;

            CommandOutputMessage commandMessage = output.getMessages().front();
            Logger::log(
                commandMessage.isSuccessful ? Logger::LogLevel::Info : Logger::LogLevel::Error,
                "{}", commandMessage.message);
        };
    }, &mServerInstance).detach();

    mServerInstance.waitUntil(ServerInstance::InstanceState::Stopped);
};

void DedicatedServer::shutdown()
{
    mServerInstance.shutdown();
    Logger::shutdown();
};