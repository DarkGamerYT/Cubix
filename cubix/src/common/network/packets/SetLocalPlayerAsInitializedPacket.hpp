#pragma once
#include "../Packet.hpp"

class SetLocalPlayerAsInitializedPacket final : public Packet
{
public:
    int64_t playerRuntimeId;

public:
    SetLocalPlayerAsInitializedPacket()
        : Packet("SetLocalPlayerAsInitializedPacket", MinecraftPacketIds::SetLocalPlayerAsInit) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};