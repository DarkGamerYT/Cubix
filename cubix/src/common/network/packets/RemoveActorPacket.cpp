#include "RemoveActorPacket.hpp"
void RemoveActorPacket::read(BinaryStream& stream)
{
    this->actorUniqueId = BinaryStream::serialize<ActorUniqueId>::read(stream);
};

void RemoveActorPacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<ActorUniqueId>::write(this->actorUniqueId, stream);
};