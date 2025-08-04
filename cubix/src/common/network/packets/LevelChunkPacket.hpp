#pragma once
#include "../Packet.hpp"
#include "../../world/level/BlockPos.hpp"
#include "../../world/level/ChunkPos.hpp"

class LevelChunkPacket final : public Packet
{
public:
    ChunkPos chunkPosition;
    int dimensionId;
    bool requestSubChunks;
    uint32_t subChunkCount;
    unsigned short subChunkLimit;
    bool cacheEnabled;
    std::vector<uint64_t> blobIds;
    std::vector<uint8_t> chunkData;

public:
    LevelChunkPacket()
        : Packet("LevelChunkPacket", MinecraftPacketIds::FullChunkData) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};