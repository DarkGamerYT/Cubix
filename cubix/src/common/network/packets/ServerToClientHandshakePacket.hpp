#pragma once
#include "../Packet.hpp"

class ServerToClientHandshakePacket : public Packet
{
public:
    std::string handshakeWebtoken;

public:
    ServerToClientHandshakePacket()
        : Packet(
            "ServerToClientHandshakePacket",
            MinecraftPacketIds::ServerToClientHandshake) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};