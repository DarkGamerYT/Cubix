#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorRuntimeId.hpp"

#include "types/PlayerActionType.hpp"

class PlayerActionPacket final : public Packet
{
public:
    ActorRuntimeId actorRuntimeId;
    PlayerActionType actionType = PlayerActionType::Unknown;
    BlockPos blockPos;
    BlockPos resultPos;
    int face;

public:
    PlayerActionPacket()
        : Packet("PlayerActionPacket", MinecraftPacketIds::PlayerAction) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
