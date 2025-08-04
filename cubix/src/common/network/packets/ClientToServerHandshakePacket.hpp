#pragma once
#include "../Packet.hpp"

class ClientToServerHandshakePacket final : public Packet
{
public:
    ClientToServerHandshakePacket()
        : Packet(
            "ClientToServerHandshakePacket",
            MinecraftPacketIds::ClientToServerHandshake) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};