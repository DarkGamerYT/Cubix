#include "ToastRequestPacket.hpp"
void ToastRequestPacket::read(BinaryStream& stream)
{
    this->title = stream.readString<Endianness::NetworkEndian>();
    this->content = stream.readString<Endianness::NetworkEndian>();
};

void ToastRequestPacket::write(BinaryStream& stream)
{
    stream.writeString<Endianness::NetworkEndian>(this->title);
    stream.writeString<Endianness::NetworkEndian>(this->content);
};