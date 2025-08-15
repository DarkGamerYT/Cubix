#include "SetLocalPlayerAsInitializedPacket.hpp"
void SetLocalPlayerAsInitializedPacket::read(BinaryStream& stream)
{
    this->playerRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);
};

void SetLocalPlayerAsInitializedPacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<ActorRuntimeId>::write(this->playerRuntimeId, stream);
};