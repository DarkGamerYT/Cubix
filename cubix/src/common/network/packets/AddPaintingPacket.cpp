#include "AddPaintingPacket.hpp"
void AddPaintingPacket::read(BinaryStream& stream)
{
    this->actorUniqueId = BinaryStream::serialize<ActorUniqueId>::read(stream);
    this->actorRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);
    this->position = stream.readVec3();
    this->direction = stream.readSignedVarInt();
    this->motif = stream.readString();
};

void AddPaintingPacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<ActorUniqueId>::write(this->actorUniqueId, stream);
    BinaryStream::serialize<ActorRuntimeId>::write(this->actorRuntimeId, stream);
    stream.writeVec3(this->position);
    stream.writeSignedVarInt(this->direction);
    stream.writeString(motif);
};