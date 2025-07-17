#include "RespawnPacket.hpp"
void RespawnPacket::read(BinaryStream& stream)
{
    this->position = stream.readVec3();
    this->state = (PlayerRespawnState)stream.readByte();
    this->playerRuntimeId = stream.readUnsignedVarLong();
};

void RespawnPacket::write(BinaryStream& stream)
{
    stream.writeVec3(this->position);
    stream.writeByte((int8_t)this->state);
    stream.writeUnsignedVarLong(this->playerRuntimeId);
};