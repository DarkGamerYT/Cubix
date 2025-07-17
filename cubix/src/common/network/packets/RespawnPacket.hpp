#pragma once
#include "../Packet.hpp"
#include "../../world/phys/Vec3.hpp"

enum class PlayerRespawnState
{
    SearchingForSpawn = 0,
    ReadyToSpawn = 1,
    ClientReadyToSpawn = 2
};

class RespawnPacket : public Packet
{
public:
    Vec3 position;
    PlayerRespawnState state;
    uint64_t playerRuntimeId;

public:
    RespawnPacket()
        : Packet("RespawnPacket", MinecraftPacketIds::Respawn) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};