#include "SetActorMotionPacket.hpp"
void SetActorMotionPacket::read(BinaryStream& stream)
{
    this->actorRuntimeId = stream.readSignedVarLong();
    this->position = stream.readVec3();
    this->tick = stream.readUnsignedVarLong();
};

void SetActorMotionPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarLong(this->actorRuntimeId);
    stream.writeVec3(this->position);
    stream.writeUnsignedVarLong(this->tick);
};