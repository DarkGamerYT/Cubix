#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorUniqueId.hpp"
#include "../../world/actor/ActorRuntimeId.hpp"

class AddPaintingPacket final : public Packet
{
public:
    ActorUniqueId actorUniqueId{ -1 };
    ActorRuntimeId actorRuntimeId{ 0 };
    Vec3 position;
    int direction;
    std::string motif;

public:
    AddPaintingPacket()
        : Packet("AddPaintingPacket", MinecraftPacketIds::AddPainting) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
