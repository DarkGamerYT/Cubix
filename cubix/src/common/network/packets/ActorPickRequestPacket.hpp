#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorUniqueId.hpp"

class ActorPickRequestPacket final : public Packet
{
public:
    ActorUniqueId actorId;
    bool withData = false;
    uint8_t emptySlots = 0;

public:
    ActorPickRequestPacket()
        : Packet("ActorPickRequestPacket", MinecraftPacketIds::ActorPickRequest) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
