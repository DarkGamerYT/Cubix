#include "ShowCreditsPacket.hpp"
void ShowCreditsPacket::read(BinaryStream& stream)
{
    this->playerRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);
    this->state = static_cast<CreditsState>(stream.readSignedVarInt());
};

void ShowCreditsPacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<ActorRuntimeId>::write(this->playerRuntimeId, stream);
    stream.writeSignedVarInt(static_cast<int32_t>(this->state));
};