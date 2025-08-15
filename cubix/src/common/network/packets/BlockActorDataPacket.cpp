#include "BlockActorDataPacket.hpp"
void BlockActorDataPacket::read(BinaryStream& stream)
{
    this->position = stream.readBlockPosition<Endianness::NetworkEndian>();
    //this->actorData = Nbt::read();
};

void BlockActorDataPacket::write(BinaryStream& stream)
{
    stream.writeBlockPosition<Endianness::NetworkEndian>(this->position);
    Nbt::write<Endianness::NetworkEndian>(stream, this->actorData.copy());
};