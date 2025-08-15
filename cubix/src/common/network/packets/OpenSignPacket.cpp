#include "OpenSignPacket.hpp"
void OpenSignPacket::read(BinaryStream& stream)
{
    this->position = stream.readBlockPosition<Endianness::NetworkEndian>();
    this->isFrontSide = stream.readBoolean();
};

void OpenSignPacket::write(BinaryStream& stream)
{
    stream.writeBlockPosition<Endianness::NetworkEndian>(position);
    stream.writeBoolean(this->isFrontSide);
};