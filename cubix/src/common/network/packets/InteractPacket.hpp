#pragma once
#include "../Packet.hpp"
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
    int64_t targetRuntimeId;
    Vec3 position;

public:
    InteractPacket()
        : Packet("InteractPacket", MinecraftPacketIds::Interact) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};