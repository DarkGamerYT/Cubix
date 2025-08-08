#pragma once
#include "../Packet.hpp"

#include "../../world/phys/Vec3.hpp"

class SetActorMotionPacket final : public Packet
{
public:
    int64_t actorRuntimeId;
    Vec3 position;
    uint64_t tick;

public:
    SetActorMotionPacket()
        : Packet("SetActorMotionPacket", MinecraftPacketIds::SetActorMotion) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};