#include "TransferPacket.hpp"
void TransferPacket::read(BinaryStream& stream)
{
    this->address = stream.readString();
    this->port = stream.readUnsignedShort();
    this->reloadWorld = stream.readBoolean();
};

void TransferPacket::write(BinaryStream& stream)
{
    stream.writeString(this->address);
    stream.writeUnsignedShort(this->port);
    stream.writeBoolean(this->reloadWorld);
};