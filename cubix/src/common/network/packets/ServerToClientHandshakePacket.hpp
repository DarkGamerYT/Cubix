#pragma once
#include "../Packet.hpp"

class ServerToClientHandshakePacket final : public Packet
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