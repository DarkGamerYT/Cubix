#pragma once
#include "../Packet.hpp"

#include "../../registry/ItemRegistry.hpp"
#include "../../nbt/NbtIo.hpp"

class ItemRegistryPacket final : public Packet
{
public:
    ItemRegistryPacket()
        : Packet("ItemRegistryPacket", MinecraftPacketIds::ItemRegistryPacket) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};