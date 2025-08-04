#pragma once
#include "../Packet.hpp"

class ChunkRadiusUpdatedPacket final : public Packet
{
public:
    int chunkRadius;

public:
    ChunkRadiusUpdatedPacket()
        : Packet("ChunkRadiusUpdatedPacket", MinecraftPacketIds::ChunkRadiusUpdated) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};