#pragma once
#include "../Packet.hpp"

#include "types/PlayStatus.hpp"

class PlayStatusPacket final : public Packet
{
public:
    PlayStatus status;

public:
    PlayStatusPacket()
        : Packet("PlayStatusPacket", MinecraftPacketIds::PlayStatus) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
