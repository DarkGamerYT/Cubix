#include "ServerToClientHandshakePacket.hpp"
void ServerToClientHandshakePacket::read(BinaryStream& stream)
{
    this->handshakeWebtoken = stream.readString();
};

void ServerToClientHandshakePacket::write(BinaryStream& stream)
{
    stream.writeString(this->handshakeWebtoken);
};