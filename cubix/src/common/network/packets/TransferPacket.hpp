#pragma once
#include "../Packet.hpp"

class TransferPacket : public Packet
{
public:
    std::string address;
    unsigned short port;
    bool reloadWorld;

public:
    TransferPacket()
        : Packet("TransferPacket", MinecraftPacketIds::Transfer) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};