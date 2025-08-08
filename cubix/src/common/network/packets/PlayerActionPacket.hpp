#pragma once
#include "../Packet.hpp"

class PlayerActionPacket final : public Packet
{
public:
    uint64_t actorRuntimeId;

public:
    PlayerActionPacket()
        : Packet("PlayerActionPacket", MinecraftPacketIds::PlayerAction) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};