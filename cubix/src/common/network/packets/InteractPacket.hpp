#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorRuntimeId.hpp"
#include "../../world/phys/Vec3.hpp"

class InteractPacket final : public Packet
{
public:
    enum class Action
    {
        Invalid = 0,
        StopRiding = 3,
        InteractUpdate,
        NpcOpen,
        OpenInventory
    };

    Action action;
    ActorRuntimeId actorRuntimeId{ 0 };
    Vec3 position;

public:
    InteractPacket()
        : Packet("InteractPacket", MinecraftPacketIds::Interact) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};