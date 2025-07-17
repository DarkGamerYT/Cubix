#include "NetworkSettingsPacket.hpp"
void NetworkSettingsPacket::read(BinaryStream& stream)
{
    this->compressionThreshold = stream.readUnsignedShort();
    this->compressionAlgorithm = static_cast<CompressionType>(static_cast<uint8_t>(stream.readUnsignedShort()));
    this->clientThrottle = stream.readBoolean();
    this->clientThrottleThreshold = stream.readByte();
    this->clientThrottleScalar = static_cast<float>(stream.readUnsignedInt());
};

void NetworkSettingsPacket::write(BinaryStream& stream)
{
    if (this->compressionAlgorithm == CompressionType::None)
        stream.writeUnsignedShort(0);
    else
        stream.writeUnsignedShort(this->compressionThreshold);
    stream.writeUnsignedShort(static_cast<uint16_t>(this->compressionAlgorithm));
    stream.writeBoolean(this->clientThrottle);
    stream.writeByte(this->clientThrottleThreshold);
    stream.writeUnsignedInt(static_cast<uint32_t>(this->clientThrottleScalar));
};