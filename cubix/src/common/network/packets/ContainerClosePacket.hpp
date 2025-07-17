#pragma once
#include "../Packet.hpp"
#include "ContainerOpenPacket.hpp"

class ContainerClosePacket : public Packet
{
public:
    uint8_t containerId;
    ContainerType containerType;
    bool serverInitiatedClose;

public:
    ContainerClosePacket()
        : Packet("ContainerClosePacket", MinecraftPacketIds::ContainerClose) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};