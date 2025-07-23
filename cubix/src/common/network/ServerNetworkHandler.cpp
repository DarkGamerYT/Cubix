#include "ServerNetworkHandler.hpp"

#include "../server/ServerInstance.hpp"

inline AppPlatform g_AppPlatform;
ServerNetworkHandler::ServerNetworkHandler(
    ServerInstance* serverInstance,
    const ConnectionDefinition& connectionDefintion
) {
    this->m_ServerInstance = serverInstance;
    this->m_ConnectionDefinition = connectionDefintion;
};

ServerNetworkHandler::~ServerNetworkHandler()
{

};

void ServerNetworkHandler::initializeNetwork()
{
    switch (this->getTransportLayer())
    {
        case TransportLayer::RakNet:
            this->m_NetworkServer = std::make_unique<RakNetServer>(this); break;
        case TransportLayer::NetherNet:
            this->m_NetworkServer = std::make_unique<NetherNetServer>(this); break;

        default: return;
    };
    
    Logger::log(Logger::LogLevel::Debug,
        "NetworkSession started with TransportLayer ({})",
            static_cast<int>(this->getTransportLayer()));
    Logger::log(Logger::LogLevel::Debug,
        "Multiplayer correlation ID: {}", this->m_NetworkServer->m_Identifier.getCorrelationId());

    this->m_NetworkServer->startServer(
        this->m_ConnectionDefinition.serverPorts,
        this->m_ConnectionDefinition.maxPlayers);
};

void ServerNetworkHandler::shutdown() {
    for (const auto &clients: this->m_Players | std::views::values)
    {
        const auto& player = clients.at(SubClientId::PrimaryClient);
        player->disconnect(DisconnectReason::RequestServerShutdown,
            false, "disconnectionScreen.hostSuspended");
    };

    this->m_NetworkServer->stopServer();
    if (this->m_ServerInstance->getInstanceState() == ServerInstance::InstanceState::Running)
    {
        this->m_ServerInstance->shutdown();
    };
};

inline const std::string& serverVersion = SharedConstants::CurrentGameVersion.asString();
void ServerNetworkHandler::onTick(uint32_t nTick)
{
    if (this->m_ServerInstance->getInstanceState() != ServerInstance::InstanceState::Running)
        return;

    this->m_NetworkServer->update();

    // Unconnected Pong
    const bool isEducationEdition = false;
    const bool isNintendoLimited = false;

    std::string unconnectedPong = std::format(
        "{};{};{};{};{};{};{};{};{};{};{};{};",
        (isEducationEdition ? "MCEE" : "MCPE"),

        "Dedicated Server",
        std::to_string(SharedConstants::NetworkProtocolVersion),
        serverVersion,
        std::to_string(this->m_Players.size()),
        std::to_string(this->m_ConnectionDefinition.maxPlayers),
        std::to_string(this->m_NetworkServer->m_Identifier.getHash()),
        "Bedrock level",
        "Survival",
        std::to_string(!isNintendoLimited),
        std::to_string(this->m_ConnectionDefinition.serverPorts.mPortV4),
        std::to_string(this->m_ConnectionDefinition.serverPorts.mPortV6));

    unconnectedPong.insert(unconnectedPong.begin(), static_cast<signed char>(unconnectedPong.size()));
    unconnectedPong.insert(unconnectedPong.begin(), 0x00);

    this->m_NetworkServer->m_UnconnectedPong = unconnectedPong;
};

void ServerNetworkHandler::onTickPlayers(uint32_t nTick) {
    std::thread([this, nTick] {
        for (const auto& client : this->m_Players | std::views::values)
            for (const auto& player : client | std::views::values)
            {
                if (player == nullptr)
                    continue;

                //player->tick();
            };
    }).detach();
};

void ServerNetworkHandler::onConnect(NetworkIdentifier& networkIdentifier)
{
    const auto& networkPeer = std::make_shared<NetworkPeer>(networkIdentifier, this->m_NetworkServer.get());
    this->m_Connections.emplace(networkIdentifier, networkPeer);
};

void ServerNetworkHandler::onDisconnect(const NetworkIdentifier& networkIdentifier)
{
    if (!this->m_Connections.contains(networkIdentifier))
        return;

    if (this->m_Players.contains(networkIdentifier))
    {
        const auto& clients = this->m_Players.at(networkIdentifier);
        for (const auto& player : clients | std::views::values)
        {
            if (player != nullptr)
            {
                const auto& connection = player->getConnection();

                Logger::log(Logger::LogLevel::Info,
                    "Player disconnected: {}, XUID: {}, Pfid: {}",
                        player->getDisplayName(),
                        connection->getXuid(), connection->getPlayFabId());
            };
        };

        this->m_Players.erase(networkIdentifier);
    };

    this->m_Connections.erase(networkIdentifier);
};

void ServerNetworkHandler::disconnectClient(
    const NetworkIdentifier& networkIdentifier,
    const SubClientId subClientId,
    const DisconnectReason disconnectReason,
    const bool skipMessage,
    const std::string& message
) {
    const std::shared_ptr<NetworkPeer>& networkPeer = this->m_Connections.at(networkIdentifier);

    DisconnectPacket disconnectPacket;
    disconnectPacket.reason = disconnectReason;
    disconnectPacket.skipMessage = skipMessage;
    disconnectPacket.message = message;

    networkPeer->sendPacket(subClientId, disconnectPacket);
};

void ServerNetworkHandler::sendPacket(Packet& packet) {
    for (const auto& subClients: this->m_Players | std::views::values)
        for (const auto& player: subClients | std::views::values)
        {
            player->sendNetworkPacket(packet);
        };
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    BinaryStream& stream
) {
    uint32_t packetHeader = stream.readUnsignedVarInt();

    auto packetId = static_cast<MinecraftPacketIds>(packetHeader & 0x03FF);
    uint8_t subClientSenderId = (packetHeader >> 10) & 0x03;
    auto subClientTargetId = static_cast<SubClientId>((packetHeader >> 12) & 0x03);

    try
    {
        switch (packetId)
        {
            case MinecraftPacketIds::RequestNetworkSettings:
            {
                RequestNetworkSettingsPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::Login:
            {
                LoginPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::SubclientLogin:
            {
                SubClientLoginPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::ClientCacheStatus:
            {
                ClientCacheStatusPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::ResourcePackClientResponse:
            {
                ResourcePackClientResponsePacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::Interact:
            {
                InteractPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::ContainerClose:
            {
                ContainerClosePacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::Text:
            {
                TextPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::RequestChunkRadius:
            {
                RequestChunkRadiusPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::PlayerSkin:
            {
                PlayerSkinPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                try {
                    gamePacket.read(stream);
                }
                catch (...)
                {
                    this->disconnectClient(
                        networkIdentifier, subClientTargetId, DisconnectReason::SkinIssue,
                        false, "disconnectionScreen.invalidSkin");
                    break;
                };

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::CommandRequest:
            {
                CommandRequestPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::MovePlayer:
            {
                MovePlayerPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };

            default:
                break;
        };
    }
    catch (...)
    {
        this->disconnectClient(
            networkIdentifier, subClientTargetId,
            DisconnectReason::BadPacket,
            false, "%disconnectionScreen.badPacket");
    };
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    RequestNetworkSettingsPacket& packet
) {
    if (!this->m_Connections.contains(networkIdentifier))
        return;

    const std::shared_ptr<NetworkPeer>& networkPeer = this->m_Connections.at(networkIdentifier);

    const bool isOutdated = packet.protocol < SharedConstants::NetworkProtocolVersion;
    if (packet.protocol < SharedConstants::NetworkProtocolVersion
        || packet.protocol > SharedConstants::NetworkProtocolVersion)
    {
        PlayStatusPacket playStatus;
        std::string disconnectMessage;
        auto disconnectReason = DisconnectReason::Unknown;
        if (isOutdated)
        {
            playStatus.status = PlayStatus::ClientOld;

            disconnectMessage = "disconnectionScreen.outdatedClient";
            disconnectReason = DisconnectReason::OutdatedClient;
        }
        else {
            playStatus.status = PlayStatus::ServerOld;

            disconnectMessage = "disconnectionScreen.outdatedServer";
            disconnectReason = DisconnectReason::OutdatedServer;
        };

        networkPeer->sendPacket(SubClientId::PrimaryClient, playStatus);
        this->disconnectClient(
            networkIdentifier, SubClientId::PrimaryClient,
            disconnectReason, false, disconnectMessage);

        return;
    };

    constexpr auto compressionAlgorithm = CompressionType::Zlib;
    constexpr uint16_t compressionThreshold = 0x00;

    NetworkSettingsPacket networkSettings;
    networkSettings.compressionThreshold = compressionThreshold;
    networkSettings.compressionAlgorithm = compressionAlgorithm;
    networkSettings.clientThrottle = false;
    networkSettings.clientThrottleThreshold = 0;
    networkSettings.clientThrottleScalar = 0.0f;

    networkPeer->sendPacket(SubClientId::PrimaryClient, networkSettings);

    networkPeer->m_Compression = compressionAlgorithm;
    networkPeer->m_CompressionThreshold = compressionThreshold;
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    LoginPacket& packet
) {
    if (!this->m_Connections.contains(networkIdentifier) || this->m_Players.contains(networkIdentifier))
        return;

    std::shared_ptr<NetworkPeer>& networkPeer = this->m_Connections.at(networkIdentifier);

    bool isOutdated = packet.protocol < SharedConstants::NetworkProtocolVersion;
    if (packet.protocol < SharedConstants::NetworkProtocolVersion
        || packet.protocol > SharedConstants::NetworkProtocolVersion)
    {
        PlayStatusPacket playStatus;

        std::string disconnectMessage;
        auto disconnectReason = DisconnectReason::Unknown;
        if (isOutdated)
        {
            playStatus.status = PlayStatus::ClientOld;

            disconnectMessage = "disconnectionScreen.outdatedClient";
            disconnectReason = DisconnectReason::OutdatedClient;
        }
        else {
            playStatus.status = PlayStatus::ServerOld;

            disconnectMessage = "disconnectionScreen.outdatedServer";
            disconnectReason = DisconnectReason::OutdatedServer;
        };

        networkPeer->sendPacket(SubClientId::PrimaryClient, playStatus);
        this->disconnectClient(
            networkIdentifier, SubClientId::PrimaryClient,
            disconnectReason, false, disconnectMessage);

        return;
    };

    const bool useOnlineAuth = this->m_ConnectionDefinition.useOnlineAuthentication;
    if (useOnlineAuth && packet.chains.size() != 3 || packet.chains.empty())
    {
        this->disconnectClient(
            networkIdentifier, SubClientId::PrimaryClient,
            DisconnectReason::NotAuthenticated,
            false, "%disconnectionScreen.notAuthenticated");
        return;
    };

    try {
        if (
            packet.connectionRequest == nullptr
            || !packet.connectionRequest->verify(packet.chains)
        ) {
            this->disconnectClient(
                networkIdentifier, SubClientId::PrimaryClient,
                DisconnectReason::NotAuthenticated,
                false, "%disconnectionScreen.notAuthenticated");
            return;
        };
    }
    catch (...) {
        PlayStatusPacket playStatus;
        playStatus.status = PlayStatus::InvalidTenant;

        networkPeer->sendPacket(SubClientId::PrimaryClient, playStatus);
        this->disconnectClient(
            networkIdentifier, SubClientId::PrimaryClient,
            DisconnectReason::InvalidTenant);
        return;
    };


    // Is Education Edition level
    bool isEducationEditionLevel = false;
    if (packet.connectionRequest->isEduMode() != isEducationEditionLevel)
    {
        PlayStatusPacket playStatus;

        playStatus.status = PlayStatus::EditionMismatchEduToVanilla;
        std::string disconnectMessage = "%disconnectionScreen.editionMismatchEduToVanilla";
        if (isEducationEditionLevel)
        {
            playStatus.status = PlayStatus::EditionMismatchVanillaToEdu;
            disconnectMessage = "%disconnectionScreen.editionMismatchVanillaToEdu";
        };

        networkPeer->sendPacket(SubClientId::PrimaryClient, playStatus);
        this->disconnectClient(
            networkIdentifier, SubClientId::PrimaryClient,
            DisconnectReason::EditionMismatch,
            false, disconnectMessage);
    };


    // Is Editor level
    bool isEditorLevel = false;
    if (packet.connectionRequest->isEditorMode() != isEditorLevel)
    {
        PlayStatusPacket playStatus;

        playStatus.status = PlayStatus::EditorMismatchEditorToVanilla;
        std::string disconnectMessage = "%disconnectionScreen.editor.mismatchEditorToVanilla";
        auto disconnectReason = DisconnectReason::EditorMismatchVanillaWorld;
        if (isEditorLevel)
        {
            playStatus.status = PlayStatus::EditorMismatchVanillaToEditor;
            disconnectMessage = "%disconnectionScreen.editor.mismatchVanillaToEditor";
            disconnectReason = DisconnectReason::EditorMismatchEditorWorld;
        };

        networkPeer->sendPacket(SubClientId::PrimaryClient, playStatus);
        this->disconnectClient(
            networkIdentifier, SubClientId::PrimaryClient,
            disconnectReason, false, disconnectMessage);
    };

    if (true == useOnlineAuth)
    {
        // Checks if there is a player with the same xuid
        /*const auto& identifier = this->getNetworkIdentifier(packet.connectionRequest->getXuid());
        if (!identifier.isUnassigned())
        {
            this->disconnectClient(
                networkIdentifier, DisconnectReason::LoggedInOtherLocation,
                false, "disconnectionScreen.loggedinOtherLocation");
            this->m_Players.erase(networkIdentifier);
        };*/
    };

    // Inform the client that the login has been successful
    PlayStatusPacket playStatus;
    playStatus.status = PlayStatus::LoginSuccess;

    networkPeer->sendPacket(SubClientId::PrimaryClient, playStatus);

    Logger::log(Logger::LogLevel::Info,
        "Player connected: {}, XUID: {}, Pfid: {}",
            packet.connectionRequest->getDisplayName(),
            packet.connectionRequest->getXuid(), packet.connectionRequest->getPlayFabId());

    // Create a new player
    this->m_Players.insert_or_assign(networkIdentifier, Players{});
    auto& clients = this->m_Players.at(networkIdentifier);

    clients.emplace(SubClientId::PrimaryClient,
        std::make_shared<Player>(networkPeer, this, packet.connectionRequest, SubClientId::PrimaryClient));

    const auto& player = clients.at(SubClientId::PrimaryClient);
    if (player == nullptr)
    {
        this->disconnectClient(
            networkIdentifier, SubClientId::PrimaryClient,
            DisconnectReason::InvalidPlayer, false, "%disconnectionScreen.connectionLost");
        return;
    };

    try {
        SerializedSkin skin{ player->getConnection() };
        player->updateSkin(skin);
    }
    catch (...)
    {
        this->disconnectClient(
            networkIdentifier, SubClientId::PrimaryClient,
            DisconnectReason::SkinIssue,
            false, "disconnectionScreen.invalidSkin");
        return;
    };

    // Encryption
    /*ServerToClientHandshakePacket serverToClientHandshake;
    serverToClientHandshake.handshakeWebtoken = handshake;

    networkPeer->sendPacket(serverToClientHandshake);*/


    /*
     * Resource Pack info
     * > Used to skip encryption
     * > Remove once encryption is implemented since it'll be sent after "ClientToServerHandshakePacket"
     */
    ResourcePacksInfoPacket resourcePacksInfo;
    resourcePacksInfo.resourcePackRequired = false;
    resourcePacksInfo.hasAddonPacks = false;
    resourcePacksInfo.hasScripts = false;
    resourcePacksInfo.forceDisableVibrantVisuals = false;

    networkPeer->sendPacket(SubClientId::PrimaryClient, resourcePacksInfo);
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    SubClientLoginPacket& packet
) {
    if (!this->m_Connections.contains(networkIdentifier))
        return;

    const auto subClientId = packet.getSubClientId();
    std::shared_ptr<NetworkPeer>& networkPeer = this->m_Connections.at(networkIdentifier);

    const bool useOnlineAuth = this->m_ConnectionDefinition.useOnlineAuthentication;
    if (useOnlineAuth && packet.chains.size() != 3 || packet.chains.empty())
    {
        this->disconnectClient(
            networkIdentifier, subClientId,
            DisconnectReason::NotAuthenticated,
            false, "%disconnectionScreen.notAuthenticated");
        return;
    };

    try {
        if (
            packet.connectionRequest == nullptr
            || !packet.connectionRequest->verify(packet.chains)
        ) {
            this->disconnectClient(
                networkIdentifier, subClientId,
                DisconnectReason::NotAuthenticated,
                false, "%disconnectionScreen.notAuthenticated");
            return;
        };
    }
    catch (...) {
        PlayStatusPacket playStatus;
        playStatus.status = PlayStatus::InvalidTenant;

        networkPeer->sendPacket(subClientId, playStatus);
        this->disconnectClient(
            networkIdentifier, subClientId,
            DisconnectReason::InvalidTenant);
        return;
    };

    if (true == useOnlineAuth)
    {
        // Checks if there is a player with the same xuid
        /*const auto& identifier = this->getNetworkIdentifier(packet.connectionRequest->getXuid());
        if (!identifier.isUnassigned())
        {
            this->disconnectClient(
                networkIdentifier, DisconnectReason::LoggedInOtherLocation,
                false, "disconnectionScreen.loggedinOtherLocation");
            this->m_Players.erase(networkIdentifier);
        };*/
    };

    // Inform the client that the login has been successful
    PlayStatusPacket playStatus;
    playStatus.status = PlayStatus::LoginSuccess;

    networkPeer->sendPacket(subClientId, playStatus);

    // Create a new player
    auto& clients = this->m_Players.at(networkIdentifier);
    clients.insert_or_assign(subClientId,
        std::make_shared<Player>(networkPeer, this, packet.connectionRequest, subClientId));

    const auto& player = clients.at(subClientId);
    if (player == nullptr)
    {
        this->disconnectClient(
            networkIdentifier, subClientId,
            DisconnectReason::InvalidPlayer, false, "%disconnectionScreen.connectionLost");
        return;
    };

    try {
        SerializedSkin skin{ player->getConnection() };
        player->updateSkin(skin);
    }
    catch (...)
    {
        this->disconnectClient(
            networkIdentifier, subClientId,
            DisconnectReason::SkinIssue,
            false, "disconnectionScreen.invalidSkin");
        return;
    };

    player->doInitialSpawn();
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    ClientToServerHandshakePacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    ResourcePacksInfoPacket resourcePacksInfo;
    resourcePacksInfo.resourcePackRequired = false;
    resourcePacksInfo.hasAddonPacks = false;
    resourcePacksInfo.hasScripts = false;
    resourcePacksInfo.forceDisableVibrantVisuals = false;

    player->sendNetworkPacket(resourcePacksInfo);
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    ClientCacheStatusPacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    bool isCacheSupported = packet.isCacheSupported;
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    ResourcePackClientResponsePacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    switch (packet.responseStatus)
    {
        case ResourcePackResponse::Cancel:
        {

            break;
        };
        case ResourcePackResponse::Downloading:
        {

            break;
        };
        case ResourcePackResponse::DownloadingFinished:
        {
            ResourcePackStackPacket resourcePackStack;
            resourcePackStack.texturePackRequired = false;
            resourcePackStack.baseGameVersion = SharedConstants::CurrentGameVersion.asString();
            resourcePackStack.includeEditorPacks = false;

            resourcePackStack.experiments.list = {
                {"upcoming_creator_features", true},
                {"gametest", true}
            };
            resourcePackStack.experiments.experimentsEverEnabled = true;

            player->sendNetworkPacket(resourcePackStack);
            break;
        };
        case ResourcePackResponse::ResourcePackStackFinished:
        {
            player->doInitialSpawn();
            player->tick();
        };
    };
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    TextPacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    switch (packet.type)
    {
        case TextType::Chat:
        {
            this->sendPacket(packet);

            Logger::log(Logger::LogLevel::Info, "<{}> {}", packet.source, packet.message);
            break;
        };

        default: break;
    };
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    InteractPacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    switch (packet.action)
    {
        case InteractPacket::Action::OpenInventory:
        {
            player->openInventory();
            break;
        };

        default: break;
    };
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    ContainerClosePacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    player->sendNetworkPacket(packet);
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    RequestChunkRadiusPacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    //player->setClientChunkRadius(packet.chunkRadius);

    constexpr int MinTickingChunksRadius = 5;
    if (packet.chunkRadius < MinTickingChunksRadius)
        packet.chunkRadius = MinTickingChunksRadius;

    ChunkRadiusUpdatedPacket chunkRadiusUpdated;
    chunkRadiusUpdated.chunkRadius = packet.chunkRadius;
    player->sendNetworkPacket(chunkRadiusUpdated);
};


void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    PlayerSkinPacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    const auto& request = player->getConnection();

    TextPacket textPacket;
    textPacket.type = TextType::Translate;
    textPacket.isLocalized = true;
    textPacket.parameters = { player->getDisplayName() };
    textPacket.xuid = request->getXuid();

    if (packet.skin.isPersona())
        textPacket.message = "%multiplayer.player.changeToPersona";
    else {
        textPacket.message = "%multiplayer.player.changeToSkin";
    };

    player->updateSkin(packet.skin);
    this->sendPacket(packet);
    this->sendPacket(textPacket);

    Logger::log(Logger::LogLevel::Debug,
        "{} changed skin from '{}' to '{}'",
            player->getDisplayName(), packet.oldSkinName, packet.newSkinName);
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    CommandRequestPacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    Logger::log(Logger::LogLevel::Debug,
        "{} executed a command: {}", player->getDisplayName(), packet.command);

    CommandOutput commandOutput{ CommandOutputType::LastOutput };
    switch (packet.commandOrigin->getType())
    {
        case CommandOriginType::Player: {
            const PlayerCommandOrigin playerOrigin{ this->m_ServerInstance, player, packet.commandOrigin };

            this->m_ServerInstance->runCommand(packet.command, playerOrigin, commandOutput);

            {
                CommandOutputPacket commandOutputPacket;
                commandOutputPacket.commandOrigin = std::make_unique<CommandOrigin>(playerOrigin);
                commandOutputPacket.commandOutput = commandOutput;

                player->sendNetworkPacket(commandOutputPacket);
            };
            break;
        };

        default:
            break;
    };
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    MovePlayerPacket& packet
) {
    if (!this->m_Players.contains(networkIdentifier))
        return;

    const std::shared_ptr<Player>& player = this->m_Players.at(networkIdentifier)[packet.getSubClientId()];
    if (player == nullptr)
        return;

    player->moveTo(packet.position, packet.rotation);
};