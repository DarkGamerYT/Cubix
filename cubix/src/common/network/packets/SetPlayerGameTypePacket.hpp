#pragma once
#include "../Packet.hpp"
#include "../../world/GameMode.hpp"

class SetPlayerGameTypePacket : public Packet
{
public:
    GameType gameType;

public:
    SetPlayerGameTypePacket()
        : Packet("SetPlayerGameTypePacket", MinecraftPacketIds::SetPlayerGameType) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
