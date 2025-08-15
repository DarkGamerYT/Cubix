#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorRuntimeId.hpp"

enum class AnimateAction {
    NoAction         = 0,
    Swing            = 1,
    WakeUp           = 3,
    CriticalHit      = 4,
    MagicCriticalHit = 5,

    RowRight         = 0 | 0x80,
    RowLeft          = 1 | 0x80
};

class AnimatePacket final : public Packet
{
public:
    ActorRuntimeId actorRuntimeId{ 0 };
    AnimateAction action = AnimateAction::NoAction;
    float rowingTime = 0;

public:
    AnimatePacket()
        : Packet("AnimatePacket", MinecraftPacketIds::Animate) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
