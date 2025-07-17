#pragma once
#include "../Packet.hpp"

class SetTimePacket : public Packet
{
public:
    int32_t time;

public:
    SetTimePacket()
        : Packet("SetTimePacket", MinecraftPacketIds::SetTime) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};