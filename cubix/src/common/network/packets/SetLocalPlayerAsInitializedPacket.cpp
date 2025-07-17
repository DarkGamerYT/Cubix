#include "SetLocalPlayerAsInitializedPacket.hpp"
void SetLocalPlayerAsInitializedPacket::read(BinaryStream& stream)
{
    this->playerRuntimeId = stream.readSignedVarLong();
};

void SetLocalPlayerAsInitializedPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarLong(this->playerRuntimeId);
};