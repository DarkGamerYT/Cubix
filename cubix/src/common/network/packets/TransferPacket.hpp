#pragma once
#include "../Packet.hpp"

class TransferPacket final : public Packet
{
public:
    std::string address;
    uint16_t port;
    bool reloadWorld;

public:
    TransferPacket()
        : Packet("TransferPacket", MinecraftPacketIds::Transfer) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};