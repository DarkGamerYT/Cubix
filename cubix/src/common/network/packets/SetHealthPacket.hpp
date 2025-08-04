#pragma once
#include "../Packet.hpp"

class SetHealthPacket final : public Packet
{
public:
    int32_t health;

public:
    SetHealthPacket()
        : Packet("SetHealthPacket", MinecraftPacketIds::SetHealth) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};