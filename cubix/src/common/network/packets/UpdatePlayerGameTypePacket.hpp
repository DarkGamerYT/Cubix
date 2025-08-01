#pragma once
#include "../Packet.hpp"
#include "../../world/GameMode.hpp"

class UpdatePlayerGameTypePacket : public Packet
{
public:
    GameType gameType = GameType::Survival;
    int64_t playerActorId = 0;
    uint64_t tick = 0;

public:
    UpdatePlayerGameTypePacket()
        : Packet("UpdatePlayerGameTypePacket", MinecraftPacketIds::UpdatePlayerGameType) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
