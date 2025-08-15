#include "AnimatePacket.hpp"
void AnimatePacket::read(BinaryStream& stream)
{
    this->action = static_cast<AnimateAction>(stream.readSignedVarInt());
    this->actorRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);

    if ((static_cast<int>(this->action) & 0x80) != 0)
        this->rowingTime = stream.read<float>();
};

void AnimatePacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(static_cast<int>(this->action));
    BinaryStream::serialize<ActorRuntimeId>::write(this->actorRuntimeId, stream);

    if ((static_cast<int>(this->action) & 0x80) != 0)
        stream.write<float>(this->rowingTime);
};