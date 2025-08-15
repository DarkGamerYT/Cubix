#pragma once
#include "../Packet.hpp"

class RequestNetworkSettingsPacket final : public Packet
{
public:
    uint32_t protocol = SharedConstants::NetworkProtocolVersion;

public:
    RequestNetworkSettingsPacket()
        : Packet(
            "RequestNetworkSettingsPacket",
            MinecraftPacketIds::RequestNetworkSettings) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};