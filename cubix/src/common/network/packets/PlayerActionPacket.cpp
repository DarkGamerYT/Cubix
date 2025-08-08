#include "PlayerActionPacket.hpp"
void PlayerActionPacket::read(BinaryStream& stream)
{
    this->actorRuntimeId = stream.readUnsignedVarLong();
};

void PlayerActionPacket::write(BinaryStream& stream)
{
    stream.writeUnsignedVarLong(this->actorRuntimeId);
};