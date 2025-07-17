#include "SetHealthPacket.hpp"
void SetHealthPacket::read(BinaryStream& stream)
{
    this->health = stream.readSignedVarInt();
};

void SetHealthPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(this->health);
};