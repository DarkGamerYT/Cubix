#include "ServerNetworkHandler.hpp"

#include "../../server/ServerInstance.hpp"
#include "../packets/MovePlayerPacket.hpp"

inline AppPlatform g_AppPlatform;
ServerNetworkHandler::ServerNetworkHandler(
    const std::shared_ptr<ServerLevel>& level,
    ServerInstance* serverInstance,
    const ConnectionDefinition& connectionDefintion,
    const bool requireOnlineAuthentication
) {
    this->mLevel = level;
    this->mServerInstance = serverInstance;
    this->mConnectionDefinition = connectionDefintion;
    this->mRequireOnlineAuthentication = requireOnlineAuthentication;
};

ServerNetworkHandler::~ServerNetworkHandler()
{

};

void ServerNetworkHandler::initializeNetwork()
{
    switch (this->getTransportLayer())
    {
        case TransportLayer::RakNet:
            this->mNetworkServer = std::make_unique<RakNetServer>(this); break;
        case TransportLayer::NetherNet:
            this->mNetworkServer = std::make_unique<NetherNetServer>(this); break;

        default: return;
    };
    
    Logger::log(Logger::LogLevel::Debug,
        "Network session started with TransportLayer ({})",
            static_cast<int>(this->getTransportLayer()));
    Logger::log(Logger::LogLevel::Debug,
        "Multiplayer Correlation Id: {}", this->mNetworkServer->mIdentifier.getCorrelationId());

    this->mNetworkServer->startServer(
        this->mConnectionDefinition.serverPorts,
        this->mConnectionDefinition.maxPlayers);
};

std::vector<std::shared_ptr<NetworkPeer>> ServerNetworkHandler::getConnections() const {
    std::vector<std::shared_ptr<NetworkPeer>> peers;
    for (const auto& networkPeer : this->mConnections | std::views::values)
        peers.emplace_back(networkPeer);

    return peers;
};
std::vector<std::shared_ptr<ServerPlayer>> ServerNetworkHandler::getPlayers() const {
    std::vector<std::shared_ptr<ServerPlayer>> players;
    for (const auto& client : this->mPlayers | std::views::values)
        for (const auto& player : client | std::views::values)
        {
            if (player == nullptr)
                continue;

            players.emplace_back(player);
        };

    return players;
};

std::shared_ptr<ServerPlayer> ServerNetworkHandler::createNewPlayer(
    const NetworkIdentifier& networkIdentifier,
    SubClientId subClientId,
    std::unique_ptr<ConnectionRequest>& connectionRequest
) {
    const std::shared_ptr<NetworkPeer>& networkPeer = this->mConnections.at(networkIdentifier);
    const auto& player = std::make_shared<ServerPlayer>(
        this->mLevel,
        networkPeer, this,
        connectionRequest, subClientId);

    if (player == nullptr)
    {
        this->disconnectClient(
            networkIdentifier, subClientId,
            DisconnectReason::InvalidPlayer, false, "%disconnectionScreen.connectionLost");
        return nullptr;
    };

    const auto& connection = player->getConnection();
    const auto& actorUniqueId = ActorUniqueId::fromUUID(connection->getSelfSignedId());
    player->setUniqueId(actorUniqueId);

    try {
        SerializedSkin skin{ connection };
        player->updateSkin(skin);
    }
    catch (...)
    {
        this->disconnectClient(
            networkIdentifier, subClientId,
            DisconnectReason::SkinIssue,
            false, "disconnectionScreen.invalidSkin");
        return nullptr;
    };

    {
        PlayerListPacket playerList;
        playerList.action = PlayerListPacket::Action::Add;
        playerList.players.emplace_back(player);

        this->sendPacket(playerList);
    };

    auto& clients = this->mPlayers.try_emplace(networkIdentifier).first->second;
    clients[subClientId] = player;
    return player;
};

std::shared_ptr<ServerPlayer> ServerNetworkHandler::getServerPlayer(const NetworkIdentifier& networkIdentifier, const SubClientId subClientId) {
    if (!this->mPlayers.contains(networkIdentifier))
        return nullptr;

    const std::shared_ptr<ServerPlayer>& player = this->mPlayers.at(networkIdentifier)[subClientId];
    if (player == nullptr)
        return nullptr;

    return player;
};
std::shared_ptr<ServerPlayer> ServerNetworkHandler::getPlayer(const NetworkIdentifier& networkIdentifier, const SubClientId subClientId, const ActorUniqueId& uniqueId) {
    const auto& player = this->getServerPlayer(networkIdentifier, subClientId);
    if (player == nullptr)
        return nullptr;

    if (player->getUniqueId() != uniqueId)
        return nullptr;

    return player;
};
std::shared_ptr<ServerPlayer> ServerNetworkHandler::getPlayer(const NetworkIdentifier& networkIdentifier, const SubClientId subClientId, const ActorRuntimeId& runtimeId) {
    const auto& player = this->getServerPlayer(networkIdentifier, subClientId);
    if (player == nullptr)
        return nullptr;

    if (player->getRuntimeId() != runtimeId)
        return nullptr;

    return player;
};

void ServerNetworkHandler::shutdown() {
    for (const auto &clients: this->mPlayers | std::views::values)
    {
        const auto& player = clients.at(SubClientId::PrimaryClient);
        player->disconnect(DisconnectReason::RequestServerShutdown,
            false, "disconnectionScreen.hostSuspended");
    };

    this->mNetworkServer->stopServer();
    if (this->mServerInstance->getInstanceState() == ServerInstance::InstanceState::Running)
    {
        this->mServerInstance->shutdown();
    };
};

inline const std::string& serverVersion = SharedConstants::CurrentGameVersion.asString();
void ServerNetworkHandler::onTick(uint32_t nTick)
{
    if (this->mServerInstance->getInstanceState() != ServerInstance::InstanceState::Running)
        return;

    this->mNetworkServer->update();

    // Unconnected Pong
    constexpr bool isEducationEdition = false;
    constexpr bool isNintendoLimited = false;

    std::string unconnectedPong = std::format(
        "{};{};{};{};{};{};{};{};{};{};{};{};",
        (isEducationEdition ? "MCEE" : "MCPE"),

        "Dedicated Server",
        std::to_string(SharedConstants::NetworkProtocolVersion),
        serverVersion,
        std::to_string(this->mPlayers.size()),
        std::to_string(this->mConnectionDefinition.maxPlayers),
        std::to_string(this->mNetworkServer->mIdentifier.getHash()),
        "Bedrock level",
        "Survival",
        std::to_string(!isNintendoLimited),
        std::to_string(this->mConnectionDefinition.serverPorts.mPortV4),
        std::to_string(this->mConnectionDefinition.serverPorts.mPortV6));

    unconnectedPong.insert(unconnectedPong.begin(), static_cast<signed char>(unconnectedPong.size()));
    unconnectedPong.insert(unconnectedPong.begin(), 0x00);

    this->mNetworkServer->mUnconnectedPong = unconnectedPong;
};

void ServerNetworkHandler::onTickPlayers(uint32_t nTick) {
    std::thread([this, nTick] {
        for (const auto& player : this->getPlayers())
        {
            if (!player->isPlayerInitialized())
                continue;

            // player->tick();
        };
    }).detach();
};

void ServerNetworkHandler::onConnect(NetworkIdentifier& networkIdentifier)
{
    const auto& networkPeer = std::make_shared<NetworkPeer>(networkIdentifier, this->mNetworkServer.get());
    this->mConnections.emplace(networkIdentifier, networkPeer);
};

void ServerNetworkHandler::onDisconnect(const NetworkIdentifier& networkIdentifier)
{
    if (!this->mConnections.contains(networkIdentifier))
        return;

    if (this->mPlayers.contains(networkIdentifier))
    {
        for (const auto& player : this->mPlayers.at(networkIdentifier) | std::views::values)
        {
            if (player == nullptr)
                continue;

            const auto& connection = player->getConnection();

            Logger::log(Logger::LogLevel::Info,
                "Player disconnected: {}, XUID: {}, Pfid: {}",
                player->getDisplayName(),
                connection->getXuid(), connection->getPlayFabId());
        };

        this->mPlayers.erase(networkIdentifier);
    };

    this->mConnections.erase(networkIdentifier);
};

void ServerNetworkHandler::disconnectClient(
    const NetworkIdentifier& networkIdentifier,
    const SubClientId subClientId,
    const DisconnectReason disconnectReason,
    const bool skipMessage,
    const std::string& message
) {
    const std::shared_ptr<NetworkPeer>& networkPeer = this->mConnections.at(networkIdentifier);

    DisconnectPacket disconnectPacket;
    disconnectPacket.reason = disconnectReason;
    disconnectPacket.skipMessage = skipMessage;
    disconnectPacket.message = message;

    networkPeer->sendPacket(subClientId, disconnectPacket);
};

void ServerNetworkHandler::sendPacket(Packet& packet) const {
    for (const auto& player: this->getPlayers())
        player->sendNetworkPacket(packet);
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
            case MinecraftPacketIds::SetLocalPlayerAsInit:
            {
                SetLocalPlayerAsInitializedPacket gamePacket;
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
            case MinecraftPacketIds::PlayerAuthInputPacket:
            {
                PlayerAuthInputPacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };
            case MinecraftPacketIds::Animate:
            {
                AnimatePacket gamePacket;
                gamePacket.setSubClientId(subClientTargetId);
                gamePacket.read(stream);

                this->handle(networkIdentifier, gamePacket);
                break;
            };

            default:
                Logger::log(Logger::LogLevel::Warn, "Unhandled packet: {}", static_cast<uint16_t>(packetId));
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
    if (!this->mConnections.contains(networkIdentifier))
        return;

    const std::shared_ptr<NetworkPeer>& networkPeer = this->mConnections.at(networkIdentifier);

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

    NetworkSettingsPacket networkSettings;
    networkSettings.compressionThreshold = this->mConnectionDefinition.compressionThreshold;
    networkSettings.compressionAlgorithm = this->mConnectionDefinition.compressionType;
    networkSettings.clientThrottle = false;
    networkSettings.clientThrottleThreshold = 0;
    networkSettings.clientThrottleScalar = 0.0f;

    networkPeer->sendPacket(SubClientId::PrimaryClient, networkSettings);

    networkPeer->mCompression = this->mConnectionDefinition.compressionType;
    networkPeer->mCompressionThreshold = this->mConnectionDefinition.compressionThreshold;
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    LoginPacket& packet
) {
    if (!this->mConnections.contains(networkIdentifier) || this->mPlayers.contains(networkIdentifier))
        return;

    std::shared_ptr<NetworkPeer>& networkPeer = this->mConnections.at(networkIdentifier);

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

    const bool useOnlineAuthentication = this->mRequireOnlineAuthentication;
    if (useOnlineAuthentication && packet.chains.size() != 3 || packet.chains.empty())
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

    if (true == useOnlineAuthentication)
    {
        // Checks if there is a player with the same xuid
        /*const auto& identifier = this->getNetworkIdentifier(packet.connectionRequest->getXuid());
        if (!identifier.isUnassigned())
        {
            this->disconnectClient(
                networkIdentifier, DisconnectReason::LoggedInOtherLocation,
                false, "disconnectionScreen.loggedinOtherLocation");
            this->mPlayers.erase(networkIdentifier);
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

    if (this->createNewPlayer(networkIdentifier, SubClientId::PrimaryClient, packet.connectionRequest) == nullptr)
        return;

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
    if (!this->mConnections.contains(networkIdentifier))
        return;

    const auto subClientId = packet.getSubClientId();
    const std::shared_ptr<NetworkPeer>& networkPeer = this->mConnections.at(networkIdentifier);

    const bool useOnlineAuthentication = this->mRequireOnlineAuthentication;
    if (useOnlineAuthentication && packet.chains.size() != 3 || packet.chains.empty())
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

    if (true == useOnlineAuthentication)
    {
        // Checks if there is a player with the same xuid
        /*const auto& identifier = this->getNetworkIdentifier(packet.connectionRequest->getXuid());
        if (!identifier.isUnassigned())
        {
            this->disconnectClient(
                networkIdentifier, DisconnectReason::LoggedInOtherLocation,
                false, "disconnectionScreen.loggedinOtherLocation");
            this->mPlayers.erase(networkIdentifier);
        };*/
    };

    // Inform the client that the login has been successful
    PlayStatusPacket playStatus;
    playStatus.status = PlayStatus::LoginSuccess;

    networkPeer->sendPacket(subClientId, playStatus);

    const auto& player = this->createNewPlayer(networkIdentifier, subClientId, packet.connectionRequest);
    if (player == nullptr)
        return;

    // Initial spawn
    player->doInitialSpawn();
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    ClientToServerHandshakePacket& packet
) {
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
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
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
    if (player == nullptr)
        return;

    bool isCacheSupported = packet.isCacheSupported;
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    ResourcePackClientResponsePacket& packet
) {
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
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

            const auto& levelSettings = this->mLevel->getLevelSettings();
            resourcePackStack.experiments.experimentList = levelSettings->getExperiments();
            resourcePackStack.experiments.experimentsEverEnabled = levelSettings->hasHadExperiments();

            player->sendNetworkPacket(resourcePackStack);
            break;
        };
        case ResourcePackResponse::ResourcePackStackFinished:
        {
            player->doInitialSpawn();

            // Item Registry
            ItemRegistryPacket itemRegistry;
            player->sendNetworkPacket(itemRegistry);

            // Creative Content
            CreativeContentPacket creativeContent;
            player->sendNetworkPacket(creativeContent);

            // All available commands
            AvailableCommandsPacket availableCommands;
            player->sendNetworkPacket(availableCommands);
        };
    };
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    SetLocalPlayerAsInitializedPacket& packet
) {
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
    if (player == nullptr)
        return;

    player->markPlayerAsInitialized();
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    TextPacket& packet
) {
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
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
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
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
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
    if (player == nullptr)
        return;

    player->sendNetworkPacket(packet);
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    RequestChunkRadiusPacket& packet
) {
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
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
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
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
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
    if (player == nullptr)
        return;

    Logger::log(Logger::LogLevel::Debug,
        "{} executed a command: {}", player->getDisplayName(), packet.command);

    CommandOutput commandOutput{ CommandOutputType::LastOutput };
    switch (packet.commandOrigin->getType())
    {
        case CommandOriginType::Player: {
            const PlayerCommandOrigin playerOrigin{ this->mServerInstance, player, packet.commandOrigin };

            this->mServerInstance->runCommand(packet.command, playerOrigin, commandOutput);

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
    PlayerAuthInputPacket& packet
) {
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
    if (player == nullptr)
        return;

    player->moveTo(packet.position, packet.rotation);
};

void ServerNetworkHandler::handle(
    NetworkIdentifier& networkIdentifier,
    AnimatePacket& packet
) {
    const std::shared_ptr<ServerPlayer>& player = this->getServerPlayer(networkIdentifier, packet.getSubClientId());
    if (player == nullptr)
        return;

    if (packet.action != AnimateAction::Swing)
        return;

    this->sendPacket(packet);
};