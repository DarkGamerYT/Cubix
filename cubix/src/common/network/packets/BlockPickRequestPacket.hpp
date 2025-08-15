#pragma once
#include "../Packet.hpp"

class BlockPickRequestPacket final : public Packet
{
public:
    BlockPos position;
    bool withData = false;
    uint8_t emptySlots = 0;

public:
    BlockPickRequestPacket()
        : Packet("BlockPickRequestPacket", MinecraftPacketIds::BlockPickRequest) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};