#pragma once
#include "../Packet.hpp"

class RequestNetworkSettingsPacket : public Packet
{
public:
    uint32_t protocol;

public:
    RequestNetworkSettingsPacket()
        : Packet(
            "RequestNetworkSettingsPacket",
            MinecraftPacketIds::RequestNetworkSettings) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};