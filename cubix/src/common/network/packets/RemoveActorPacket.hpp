#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorUniqueId.hpp"

class RemoveActorPacket final : public Packet
{
public:
    ActorUniqueId actorUniqueId{ -1 };

public:
    RemoveActorPacket()
        : Packet("RemoveActorPacket", MinecraftPacketIds::RemoveActor) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
