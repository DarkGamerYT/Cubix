#pragma once
#include "../Packet.hpp"
#include "../../world/actor/player/SerializedSkin.hpp"

class PlayerSkinPacket final : public Packet
{
public:
    Util::UUID uuid;
    SerializedSkin skin{};
    std::string newSkinName;
    std::string oldSkinName;
    bool isMarketplaceContent = false;

public:
    PlayerSkinPacket()
        : Packet("PlayerSkinPacket", MinecraftPacketIds::PlayerSkin) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
