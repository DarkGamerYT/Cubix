#include "ContainerOpenPacket.hpp"
void ContainerOpenPacket::read(BinaryStream& stream)
{
    this->containerId = stream.readByte();
    this->containerType = (ContainerType)stream.readByte();
    this->position = stream.readNetworkBlockPosition();
    this->targetActorId = stream.readSignedVarLong();
};

void ContainerOpenPacket::write(BinaryStream& stream)
{
    stream.writeByte(this->containerId);
    stream.writeByte((uint8_t)this->containerType);
    stream.writeNetworkBlockPosition(this->position);
    stream.writeSignedVarLong(this->targetActorId);
};