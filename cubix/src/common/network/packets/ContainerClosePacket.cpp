#include "ContainerClosePacket.hpp"
void ContainerClosePacket::read(BinaryStream& stream)
{
    this->containerId = stream.readByte();
    this->containerType = (ContainerType)stream.readByte();
    this->serverInitiatedClose = stream.readBoolean();
};

void ContainerClosePacket::write(BinaryStream& stream)
{
    stream.writeByte(this->containerId);
    stream.writeByte((uint8_t)this->containerType);
    stream.writeBoolean(this->serverInitiatedClose);
};