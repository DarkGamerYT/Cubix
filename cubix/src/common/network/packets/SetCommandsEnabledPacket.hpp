#pragma once
#include "../Packet.hpp"

class SetCommandsEnabledPacket : public Packet
{
public:
    bool commandsEnabled;

public:
    SetCommandsEnabledPacket()
        : Packet("SetCommandsEnabledPacket", MinecraftPacketIds::SetCommandsEnabled) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};