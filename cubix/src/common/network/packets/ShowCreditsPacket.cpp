#include "ShowCreditsPacket.hpp"
void ShowCreditsPacket::read(BinaryStream& stream)
{
    this->playerRuntimeId = stream.readSignedVarLong();
    this->state = (CreditsState)stream.readSignedVarInt();
};

void ShowCreditsPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarLong(this->playerRuntimeId);
    stream.writeSignedVarInt((int)this->state);
};