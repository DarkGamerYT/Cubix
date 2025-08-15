#include "PlayerActionPacket.hpp"
void PlayerActionPacket::read(BinaryStream& stream)
{
    this->actorRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);
    this->actionType = static_cast<PlayerActionType>(stream.readSignedVarInt());
    this->blockPos = stream.readBlockPosition<Endianness::NetworkEndian>();
    this->resultPos = stream.readBlockPosition<Endianness::NetworkEndian>();
    this->face = stream.readSignedVarInt();
};

void PlayerActionPacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<ActorRuntimeId>::write(this->actorRuntimeId, stream);
    stream.writeSignedVarInt(static_cast<int32_t>(this->actionType));
    stream.writeBlockPosition<Endianness::NetworkEndian>(this->blockPos);
    stream.writeBlockPosition<Endianness::NetworkEndian>(this->resultPos);
    stream.writeSignedVarInt(this->face);
};