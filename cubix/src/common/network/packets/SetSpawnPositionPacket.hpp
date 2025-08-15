#pragma once
#include "../Packet.hpp"

#include "types/SpawnPositionType.hpp"

class SetSpawnPositionPacket final : public Packet
{
public:
    SpawnPositionType spawnPositionType = SpawnPositionType::WorldSpawn;
    BlockPos blockPosition;
    int dimension;
    BlockPos spawnBlockPosition;

public:
    SetSpawnPositionPacket()
        : Packet("SetSpawnPositionPacket", MinecraftPacketIds::SetSpawnPosition) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};