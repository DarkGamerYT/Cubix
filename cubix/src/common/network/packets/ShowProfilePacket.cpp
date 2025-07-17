#include "ShowProfilePacket.hpp"
void ShowProfilePacket::read(BinaryStream& stream)
{
    this->xuid = stream.readString();
};

void ShowProfilePacket::write(BinaryStream& stream)
{
    stream.writeString(this->xuid);
};