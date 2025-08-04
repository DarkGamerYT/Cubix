#pragma once
#include "../Packet.hpp"

class RequestChunkRadiusPacket final : public Packet
{
public:
    int chunkRadius;
    uint8_t maxChunkRadius;

public:
    RequestChunkRadiusPacket()
        : Packet("RequestChunkRadiusPacket", MinecraftPacketIds::RequestChunkRadius) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};