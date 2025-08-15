#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorRuntimeId.hpp"
#include "../../world/phys/Vec3.hpp"

class SetActorMotionPacket final : public Packet
{
public:
    ActorRuntimeId actorRuntimeId;
    Vec3 position;
    uint64_t tick;

public:
    SetActorMotionPacket()
        : Packet("SetActorMotionPacket", MinecraftPacketIds::SetActorMotion) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};