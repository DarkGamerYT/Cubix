#include "SetActorMotionPacket.hpp"
void SetActorMotionPacket::read(BinaryStream& stream)
{
    this->actorRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);
    this->position = stream.readVec3();
    this->tick = stream.readUnsignedVarLong();
};

void SetActorMotionPacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<ActorRuntimeId>::write(this->actorRuntimeId, stream);
    stream.writeVec3(this->position);
    stream.writeUnsignedVarLong(this->tick);
};