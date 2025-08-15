#pragma once
#include "../Packet.hpp"

#include "types/HudElement.hpp"

class SetHudPacket final : public Packet
{
public:
    std::vector<HudElement> elements;
    bool isVisible;

public:
    SetHudPacket()
        : Packet("SetHudPacket", MinecraftPacketIds::SetHudPacket) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
