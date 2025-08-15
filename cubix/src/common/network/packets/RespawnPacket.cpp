#include "RespawnPacket.hpp"
void RespawnPacket::read(BinaryStream& stream)
{
    this->position = stream.readVec3();
    this->state = static_cast<PlayerRespawnState>(stream.readByte());
    this->playerRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);
};

void RespawnPacket::write(BinaryStream& stream)
{
    stream.writeVec3(this->position);
    stream.writeByte(static_cast<int8_t>(this->state));
    BinaryStream::serialize<ActorRuntimeId>::write(this->playerRuntimeId, stream);
};