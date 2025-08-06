#pragma once
#include "../Packet.hpp"

#include "../../world/level/storage/GameRule.hpp"

class GameRulesChangedPacket final : public Packet
{
public:
    std::vector<std::shared_ptr<IGameRule>> rules;

public:
    GameRulesChangedPacket()
        : Packet(
            "GameRulesChangedPacket",
            MinecraftPacketIds::GameRulesChanged) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};