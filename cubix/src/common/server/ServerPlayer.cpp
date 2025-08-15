#include "ServerPlayer.hpp"

#include <future>

#include "../network/server/ServerNetworkHandler.hpp"

ServerPlayer::ServerPlayer(
    const std::shared_ptr<Level>& level,
    const std::shared_ptr<NetworkPeer>& networkPeer, ServerNetworkHandler* networkHandler,
    std::unique_ptr<ConnectionRequest>& connection, const SubClientId subClientId
) : Player(level, subClientId) {
    this->mLevel = level;
    this->mNetworkHandler = networkHandler;
    this->mNetworkPeer = networkPeer;
    this->mConnection = std::move(connection);

    this->setName(this->mConnection->getThirdPartyName());
};

void ServerPlayer::doInitialSpawn() {
    // Start Game
    StartGamePacket startGame;
    startGame.levelSettings = this->mLevel->getLevelSettings();

    startGame.actorUniqueId = this->getUniqueId();
    startGame.actorRuntimeId = this->getRuntimeId();
    startGame.actorGameType = GameType::Default;

    startGame.position = { 0, -59, 0 };
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
    startGame.worldTemplateId = Util::UUID{ 0, 0 };
    startGame.clientSideGeneration = false;
    startGame.blockNetworkIdsAreHashes = true;
    startGame.networkPermissions.serverAuthSoundEnabled = true;

    startGame.multiplayerCorrelationId = this->mNetworkPeer->getNetworkServer()->mIdentifier.getCorrelationId();

    startGame.levelId = "test";
    startGame.levelName = "Test";

    this->sendNetworkPacket(startGame);

    this->mIsLoading = false;
    this->mIsInitialSpawnDone = true;

    Logger::log(Logger::LogLevel::Info,
        "Player spawned: {}, XUID: {}, Pfid: {}",
            this->getDisplayName(),
            this->getConnection()->getXuid(), this->getConnection()->getPlayFabId());

    // Play Status
    PlayStatusPacket spawnPlayStatus;
    spawnPlayStatus.status = PlayStatus::PlayerSpawn;

    this->sendNetworkPacket(spawnPlayStatus);

    this->tick();
};

template <typename T, std::size_t N>
auto vectorToTuple(const std::vector<T>& vec) {
    return [&]<std::size_t... I>(std::index_sequence<I...>) {
        return std::make_tuple((I < vec.size() ? vec[I] : T{})...);
    }(std::make_index_sequence<N>());
};

void ServerPlayer::tick() {
    Player::tick();

    constexpr int renderDistance = 4;
    {
        NetworkChunkPublisherUpdatePacket networkChunkPublisher;
        networkChunkPublisher.position = BlockPos(this->getPosition());
        networkChunkPublisher.radius = renderDistance << 4;

        this->sendNetworkPacket(networkChunkPublisher);
    };

    // Chunks
    std::vector<ChunkPos> chunkPositions;
    for (int r = 0; r <= renderDistance; ++r) {
        for (int dx = -r; dx <= r; ++dx) {
            for (int dz = -r; dz <= r; ++dz) {
                if (std::abs(dx) != r && std::abs(dz) != r)
                    continue;

                const auto& chunkPos = this->getChunkPos();
                int x = chunkPos.x + dx;
                int z = chunkPos.z + dz;
                chunkPositions.emplace_back(x, z);
            };
        };
    };

    std::vector<LevelChunkPacket> chunkPackets(chunkPositions.size());

    const auto& worker = [&](const size_t start, const size_t end) {
        for (size_t i = start; i < end; ++i) {
            const auto& pos = chunkPositions[i];
            const size_t index = &pos - chunkPositions.data();

            // Chunk data stuff
            LevelChunkPacket levelChunk;
            levelChunk.chunkPosition = pos;
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
        };
    };

    const size_t threadCount = std::thread::hardware_concurrency();
    const size_t blockSize = (chunkPositions.size() + threadCount - 1) / threadCount;

    std::vector<std::future<void>> futures;
    for (size_t t = 0; t < threadCount; ++t) {
        const size_t start = t * blockSize;
        const size_t end = std::min(start + blockSize, chunkPositions.size());

        futures.push_back(std::async(
            std::launch::async,
            worker, start, end));
    };

    for (auto &f : futures)
        f.get();

    constexpr size_t batchSize = 12;
    for (size_t i = 0; i < chunkPackets.size(); i += batchSize)
    {
        using difference = std::vector<unsigned char>::difference_type;
        const auto start = chunkPackets.begin() + static_cast<difference>(i);
        const auto end = std::next(start, std::min(batchSize, chunkPackets.size() - i));

        std::vector batch(start, end);

        auto tuple = vectorToTuple<LevelChunkPacket, batchSize>(batch);
        std::apply([&](auto&... args) {
            this->mNetworkPeer->sendPacket(this->mSubClientId, args...);
        }, tuple);
    };

    {
        NetworkChunkPublisherUpdatePacket networkChunkPublisher;
        networkChunkPublisher.position = BlockPos(this->getPosition());
        networkChunkPublisher.radius = renderDistance << 4;
        networkChunkPublisher.savedChunks = chunkPositions;

        this->sendNetworkPacket(networkChunkPublisher);
    };
};

void ServerPlayer::disconnect(const DisconnectReason reason, const bool skipMessage, const std::string& message) const {
    this->mNetworkHandler->disconnectClient(
        this->mNetworkPeer->getNetworkIdentifier(),
        this->mSubClientId,
        reason, skipMessage, message);
};

void ServerPlayer::sendNetworkPacket(Packet& packet) const {
    this->mNetworkPeer->sendPacket(this->mSubClientId, packet);
};