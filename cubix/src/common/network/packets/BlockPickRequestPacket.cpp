#include "BlockPickRequestPacket.hpp"
void BlockPickRequestPacket::read(BinaryStream& stream)
{
    this->position = stream.readBlockPosition<Endianness::LittleEndian>();
    this->withData = stream.readBoolean();
    this->emptySlots = stream.readByte();
};

void BlockPickRequestPacket::write(BinaryStream& stream)
{
    stream.writeBlockPosition<Endianness::LittleEndian>(this->position);
    stream.writeBoolean(this->withData);
    stream.writeByte(this->emptySlots);
};