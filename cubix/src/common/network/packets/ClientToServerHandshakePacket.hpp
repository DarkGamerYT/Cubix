#pragma once
#include "../Packet.hpp"

class ClientToServerHandshakePacket : public Packet
{
public:
    ClientToServerHandshakePacket()
        : Packet(
            "ClientToServerHandshakePacket",
            MinecraftPacketIds::ClientToServerHandshake) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};