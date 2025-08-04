#pragma once
#include "../Packet.hpp"

class ShowStoreOfferPacket final : public Packet
{
public:
    enum class RedirectType
    {
        MarketplaceOffer = 0,
        DressingRoomOffer = 1,
        ThirdPartyServerPage = 2
    };

    std::string productId;
    RedirectType redirectType;

public:
    ShowStoreOfferPacket()
        : Packet("ShowStoreOfferPacket", MinecraftPacketIds::ShowStoreOffer) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};