#pragma once
#include "../Packet.hpp"

#include "../../nbt/NbtIo.hpp"

class BlockActorDataPacket final : public Packet
{
public:
    BlockPos position;
    Nbt::CompoundTag actorData;

public:
    BlockActorDataPacket()
        : Packet("BlockActorDataPacket", MinecraftPacketIds::BlockActorData) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};