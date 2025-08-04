#include "Player.hpp"

#include <execution>

#include "../../../network/ServerNetworkHandler.hpp"
#include "../../../network/packets/PlayerListPacket.hpp"

Player::Player(
    const std::shared_ptr<Level>& level,
    const std::shared_ptr<NetworkPeer>& networkPeer, ServerNetworkHandler* networkHandler,
    std::unique_ptr<ConnectionRequest>& connection, const SubClientId subClientId
) {
    this->mLevel = level;
    this->mNetworkHandler = networkHandler;
    this->mNetworkPeer = networkPeer;
    this->mConnection = std::move(connection);

    this->mDisplayName = this->mConnection->getThirdPartyName();
    this->mSubClientId = subClientId;
};

void Player::updateSkin(SerializedSkin& skin) {
    this->mSkin = std::move(skin);
};

void Player::move(const Vec3& position) {
    Actor::move(position);


};

template <typename T, std::size_t N>
auto vectorToTuple(const std::vector<T>& vec) {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::make_tuple((I < vec.size() ? vec[I] : T{})...);
    }(std::make_index_sequence<N>());
};

void Player::tick() {
    const int renderDistance = 5;

    NetworkChunkPublisherUpdatePacket networkChunkPublisher;
    networkChunkPublisher.position = BlockPos(this->getPosition());
    networkChunkPublisher.radius = renderDistance << 4;

    this->sendNetworkPacket(networkChunkPublisher);

    // Chunks
    std::vector<std::pair<int, int>> chunkPositions;
    for (int r = 0; r <= renderDistance; ++r) {
        for (int dx = -r; dx <= r; ++dx) {
            for (int dz = -r; dz <= r; ++dz) {
                if (std::abs(dx) != r && std::abs(dz) != r)
                    continue;

                chunkPositions.emplace_back(dx, dz);
            };
        };
    };

    std::vector<LevelChunkPacket> chunkPackets(chunkPositions.size());
    std::for_each(
        std::execution::par_unseq, chunkPositions.begin(), chunkPositions.end(),
        [&](const std::pair<int, int>& pos) {
            size_t index = &pos - chunkPositions.data();

            const auto& chunkPos = this->getChunkPos();
            int x = chunkPos.x + pos.first;
            int y = chunkPos.x + pos.second;

            // Chunk data stuff
            LevelChunkPacket levelChunk;
            levelChunk.chunkPosition = { x, y };
            levelChunk.dimensionId = 0;
            levelChunk.cacheEnabled = false;
            levelChunk.requestSubChunks = false;


            constexpr int SECTION_COUNT = 16;
            int subChunkCount = SECTION_COUNT - 1;

            Chunk chunk;
            {
                const auto& subChunks = chunk.getSubChunks();
                while (subChunkCount >= 0 && subChunks.at(subChunkCount).isEmpty()) {
                    subChunkCount--;
                };
                subChunkCount++;
            };
            levelChunk.subChunkCount = subChunkCount;

            {
                BinaryStream stream;
                chunk.serialize(stream, true);

                levelChunk.chunkData = stream.mStream;
            };

            chunkPackets[index] = levelChunk;
    });

    constexpr size_t batchSize = 10;
    for (size_t i = 0; i < chunkPackets.size(); i += batchSize)
    {
        using difference = std::vector<unsigned char>::difference_type;
        const auto start = chunkPackets.begin() + static_cast<difference>(i);
        const auto end = std::next(start, min(batchSize, chunkPackets.size() - i));

        std::vector batch(start, end);

        auto tuple = vectorToTuple<LevelChunkPacket, batchSize>(batch);
        std::apply([&](auto&... args) {
            this->sendNetworkPacket(args...);
        }, tuple);
    };
};

void Player::openInventory() const {
    ContainerOpenPacket containerOpen;
    containerOpen.targetActorId = 0;
    containerOpen.position = BlockPos{ 0.0, 0.0, 0.0 };
    containerOpen.containerId = 0;
    containerOpen.containerType = ContainerType::INVENTORY;

    this->sendNetworkPacket(containerOpen);
};

void Player::doInitialSpawn() {
    // Start Game
    StartGamePacket startGame;
    startGame.levelSettings = this->mLevel->getLevelSettings();

    startGame.targetActorId = 1;
    startGame.targetRuntimeId = 1;
    startGame.actorGameType = GameType::Default;

    startGame.position = { 0, 0, 0 };
    startGame.rotation = { 0, 0 };

    const Nbt::CompoundTag playerData;
    startGame.playerPropertyData = playerData;

    startGame.templateContentIdentity = Util::UUID{};
    startGame.isTrial = false;

    // Movement settings
    startGame.movementSettings.rewindHistorySize = 3200;
    startGame.movementSettings.serverAuthoratativeBlockBreaking = false;

    startGame.tick = 0;
    startGame.enchantmentSeed = 1;
    startGame.enableItemStackNetManager = true;
    startGame.serverVersion = "Cubix v" + SharedConstants::CurrentGameVersion.asString();
    startGame.serverBlockTypeRegistryChecksum = 0;
    startGame.worldTemplateId = { 0, 0 };
    startGame.clientSideGeneration = false;
    startGame.blockNetworkIdsAreHashes = true;
    startGame.networkPermissions.serverAuthSoundEnabled = true;

    startGame.multiplayerCorrelationId = this->mNetworkPeer->getNetworkServer()->m_Identifier.getCorrelationId();

    startGame.levelId = "test";
    startGame.levelName = "Test";

    this->sendNetworkPacket(startGame);

    Logger::log(Logger::LogLevel::Info,
        "Player spawned: {}, XUID: {}, Pfid: {}",
            this->getDisplayName(),
            this->mConnection->getXuid(), this->mConnection->getPlayFabId());

    if (this->mSubClientId == SubClientId::PrimaryClient)
    {
        // Item Registry
        ItemRegistryPacket itemRegistry;
        this->sendNetworkPacket(itemRegistry);

        // Creative Content
        CreativeContentPacket creativeContent;
        this->sendNetworkPacket(creativeContent);

        // All available commands
        AvailableCommandsPacket availableCommands;
        this->sendNetworkPacket(availableCommands);
    };

    // Play Status
    PlayStatusPacket playStatus;
    playStatus.status = PlayStatus::PlayerSpawn;

    this->sendNetworkPacket(playStatus);

    // Player list
    /*const auto& clients = this->m_NetworkHandler->getPlayers().at(this->m_NetworkPeer->getNetworkIdentifier());
    const auto& player = clients.at(this->m_SubClientId);

    PlayerListPacket playerList;
    playerList.action = PlayerListPacket::Action::Add;
    playerList.players.emplace_back(player);*/

    //this->m_NetworkHandler->sendPacket(playerList);
};

void Player::disconnect(DisconnectReason reason, bool skipMessage, const std::string& message) const {
    this->mNetworkHandler->disconnectClient(
        this->mNetworkPeer->getNetworkIdentifier(),
        this->mSubClientId,
        reason, skipMessage, message);
};