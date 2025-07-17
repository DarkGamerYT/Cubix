#include "SetTimePacket.hpp"
void SetTimePacket::read(BinaryStream& stream)
{
    this->time = stream.readSignedVarInt();
};

void SetTimePacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(this->time);
};