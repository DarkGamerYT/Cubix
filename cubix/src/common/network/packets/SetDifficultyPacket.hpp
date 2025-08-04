#pragma once
#include "../Packet.hpp"
#include "../../world/Difficulty.hpp"

class SetDifficultyPacket final : public Packet
{
public:
    Difficulty difficulty;

public:
    SetDifficultyPacket()
        : Packet("SetDifficultyPacket", MinecraftPacketIds::SetDifficulty) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};