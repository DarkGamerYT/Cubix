#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorRuntimeId.hpp"

class SetLocalPlayerAsInitializedPacket final : public Packet
{
public:
    ActorRuntimeId playerRuntimeId;

public:
    SetLocalPlayerAsInitializedPacket()
        : Packet("SetLocalPlayerAsInitializedPacket", MinecraftPacketIds::SetLocalPlayerAsInit) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
