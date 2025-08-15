#pragma once
#include "../Packet.hpp"

#include "../../world/actor/ActorRuntimeId.hpp"

class ShowCreditsPacket final : public Packet
{
public:
    enum class CreditsState
    {
        Start = 0,
        Finished = 1
    };

    ActorRuntimeId playerRuntimeId;
    CreditsState state;

public:
    ShowCreditsPacket()
        : Packet("ShowCreditsPacket", MinecraftPacketIds::ShowCredits) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
