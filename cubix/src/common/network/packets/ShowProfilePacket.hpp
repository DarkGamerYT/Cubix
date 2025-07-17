#pragma once
#include "../Packet.hpp"

class ShowProfilePacket : public Packet
{
public:
    std::string xuid;

public:
    ShowProfilePacket()
        : Packet("ShowProfilePacket", MinecraftPacketIds::ShowProfile) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};