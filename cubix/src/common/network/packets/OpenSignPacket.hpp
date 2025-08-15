#pragma once
#include "../Packet.hpp"

class OpenSignPacket final : public Packet
{
public:
    BlockPos position;
    bool isFrontSide = false;

public:
    OpenSignPacket()
        : Packet("OpenSignPacket", MinecraftPacketIds::OpenSign) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};