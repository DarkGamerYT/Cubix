#include "ContainerOpenPacket.hpp"
void ContainerOpenPacket::read(BinaryStream& stream)
{
    this->containerId = stream.readByte();
    this->containerType = static_cast<ContainerType>(stream.readByte());
    this->position = stream.readNetworkBlockPosition();
    this->actorUniqueId = stream.readSignedVarLong();
};

void ContainerOpenPacket::write(BinaryStream& stream)
{
    stream.writeByte(this->containerId);
    stream.writeByte(static_cast<uint8_t>(this->containerType));
    stream.writeNetworkBlockPosition(this->position);
    stream.writeSignedVarLong(this->actorUniqueId);
};