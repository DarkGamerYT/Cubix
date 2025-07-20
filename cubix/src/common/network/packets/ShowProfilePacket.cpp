#include "ShowProfilePacket.hpp"
void ShowProfilePacket::read(BinaryStream& stream)
{
    this->xuid = stream.readString<Endianness::NetworkEndian>();
};

void ShowProfilePacket::write(BinaryStream& stream)
{
    stream.writeString<Endianness::NetworkEndian>(this->xuid);
};