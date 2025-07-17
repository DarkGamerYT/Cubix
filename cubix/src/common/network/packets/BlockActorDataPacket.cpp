#include "BlockActorDataPacket.hpp"
void BlockActorDataPacket::read(BinaryStream& stream)
{
    this->position = stream.readNetworkBlockPosition();
    //this->actorData = Nbt::read();
};

void BlockActorDataPacket::write(BinaryStream& stream)
{
    stream.writeNetworkBlockPosition(this->position);
    Nbt::write<Endianness::NetworkEndian>(stream, this->actorData.copy());
};