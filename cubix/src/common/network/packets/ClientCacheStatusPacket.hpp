#pragma once
#include "../Packet.hpp"

class ClientCacheStatusPacket : public Packet
{
public:
    bool isCacheSupported;

public:
    ClientCacheStatusPacket()
        : Packet("ClientCacheStatusPacket", MinecraftPacketIds::ClientCacheStatus) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};