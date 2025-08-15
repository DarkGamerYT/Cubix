#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorUniqueId.hpp"
#include "../../world/inventory/ContainerType.hpp"

class ContainerOpenPacket final : public Packet
{
public:
    uint8_t containerId;
    ContainerType containerType = ContainerType::NONE;
    BlockPos position;
    ActorUniqueId actorUniqueId{ -1 };

public:
    ContainerOpenPacket()
        : Packet("ContainerOpenPacket", MinecraftPacketIds::ContainerOpen) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
