#pragma once
#include "../Packet.hpp"

class ShowCreditsPacket final : public Packet
{
public:
    enum class CreditsState
    {
        Start = 0,
        Finished = 1
    };

    int64_t playerRuntimeId;
    CreditsState state;

public:
    ShowCreditsPacket()
        : Packet("ShowCreditsPacket", MinecraftPacketIds::ShowCredits) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};