#pragma once
#include "../Packet.hpp"

class ToastRequestPacket : public Packet
{
public:
    std::string title;
    std::string content;

public:
    ToastRequestPacket()
        : Packet("ToastRequestPacket", MinecraftPacketIds::ToastRequest) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};