#pragma once
#include "../Packet.hpp"

#include "../CompressionType.hpp"

class NetworkSettingsPacket : public Packet
{
public:
    uint16_t compressionThreshold;
    CompressionType compressionAlgorithm;
    bool clientThrottle;
    uint8_t clientThrottleThreshold;
    float clientThrottleScalar;

public:
    NetworkSettingsPacket()
        : Packet("NetworkSettingsPacket", MinecraftPacketIds::NetworkSettings) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
