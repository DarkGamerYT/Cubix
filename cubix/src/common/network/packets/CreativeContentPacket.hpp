#pragma once
#include "../Packet.hpp"

#include "../../registry/ItemGroupRegistry.hpp"
#include "../../registry/ItemRegistry.hpp"

class CreativeContentPacket final : public Packet
{
public:
    CreativeContentPacket()
        : Packet("CreativeContentPacket", MinecraftPacketIds::CreativeContent) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};