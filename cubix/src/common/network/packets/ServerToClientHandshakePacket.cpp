#include "ServerToClientHandshakePacket.hpp"
void ServerToClientHandshakePacket::read(BinaryStream& stream)
{
    this->handshakeWebtoken = stream.readString<Endianness::NetworkEndian>();
};

void ServerToClientHandshakePacket::write(BinaryStream& stream)
{
    stream.writeString<Endianness::NetworkEndian>(this->handshakeWebtoken);
};