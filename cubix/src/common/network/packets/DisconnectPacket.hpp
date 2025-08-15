#pragma once
#include "../Packet.hpp"

#include "types/DisconnectReason.hpp"

class DisconnectPacket final : public Packet
{
public:
    DisconnectReason reason;
    bool skipMessage;
    std::string message;

public:
    DisconnectPacket()
        : Packet("DisconnectPacket", MinecraftPacketIds::Disconnect) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
