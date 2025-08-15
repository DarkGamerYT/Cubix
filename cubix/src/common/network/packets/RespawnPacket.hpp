#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorRuntimeId.hpp"
#include "../../world/phys/Vec3.hpp"

#include "types/PlayerRespawnState.hpp"

class RespawnPacket final : public Packet
{
public:
    Vec3 position;
    PlayerRespawnState state;
    ActorRuntimeId playerRuntimeId;

public:
    RespawnPacket()
        : Packet("RespawnPacket", MinecraftPacketIds::Respawn) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};