#pragma once
#include <vector>

#include "../Packet.hpp"
#include "../../world/actor/player/Player.hpp"

class PlayerListPacket final : public Packet
{
public:
    enum class Action {
        Add    = 0,
        Remove = 1
    };

    Action action;
    std::vector<std::shared_ptr<Player>> players;

public:
    PlayerListPacket()
        : Packet("PlayerListPacket", MinecraftPacketIds::PlayerList) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
