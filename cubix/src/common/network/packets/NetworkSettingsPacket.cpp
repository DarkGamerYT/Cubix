#include "NetworkSettingsPacket.hpp"
void NetworkSettingsPacket::read(BinaryStream& stream)
{
    this->compressionThreshold = stream.readUnsignedShort();
    this->compressionAlgorithm = stream.readUnsignedShort();
    this->clientThrottle = stream.readBoolean();
    this->clientThrottleThreshold = stream.readByte();
    this->clientThrottleScalar = (float)stream.readUnsignedInt();
};

void NetworkSettingsPacket::write(BinaryStream& stream)
{
    stream.writeUnsignedShort(this->compressionThreshold);
    stream.writeUnsignedShort(this->compressionAlgorithm);
    stream.writeBoolean(this->clientThrottle);
    stream.writeByte(this->clientThrottleThreshold);
    stream.writeUnsignedInt((uint32_t)this->clientThrottleScalar);
};