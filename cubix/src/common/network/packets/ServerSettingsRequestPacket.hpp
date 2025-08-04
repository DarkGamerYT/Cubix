#pragma once
#include "../Packet.hpp"

class ServerSettingsRequestPacket final : public Packet
{
public:
    ServerSettingsRequestPacket()
        : Packet("ServerSettingsRequestPacket", MinecraftPacketIds::ServerSettingsRequest) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};