#pragma once
#include "../Packet.hpp"
#include "../../world/level/BlockPos.hpp"
#include "../../world/level/ChunkPos.hpp"

class NetworkChunkPublisherUpdatePacket : public Packet
{
public:
    BlockPos position;
    uint32_t radius;
    std::vector<ChunkPos> savedChunks;

public:
    NetworkChunkPublisherUpdatePacket()
        : Packet(
            "NetworkChunkPublisherUpdatePacket",
            MinecraftPacketIds::NetworkChunkPublisherUpdate) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};