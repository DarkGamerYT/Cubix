#pragma once
#include "../Packet.hpp"

class ClientboundCloseFormPacket final : public Packet
{
public:
    ClientboundCloseFormPacket()
        : Packet("ClientboundCloseFormPacket", MinecraftPacketIds::ClientboundCloseScreen) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
