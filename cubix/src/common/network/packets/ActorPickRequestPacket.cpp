#include "ActorPickRequestPacket.hpp"
void ActorPickRequestPacket::read(BinaryStream& stream)
{
    this->actorId = BinaryStream::serialize<ActorUniqueId>::read(stream);
    this->emptySlots = stream.readByte();
    this->withData = stream.readBoolean();
};

void ActorPickRequestPacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<ActorUniqueId>::write(this->actorId, stream);
    stream.writeByte(this->emptySlots);
    stream.writeBoolean(this->withData);
};