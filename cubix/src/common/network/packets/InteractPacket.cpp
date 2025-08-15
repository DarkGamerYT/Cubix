#include "InteractPacket.hpp"
void InteractPacket::read(BinaryStream& stream)
{
    this->action = static_cast<InteractPacket::Action>(stream.readByte());
    this->actorRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);

    if (this->action == InteractPacket::Action::InteractUpdate
        || this->action == InteractPacket::Action::StopRiding)
    {
        this->position = stream.readVec3();
    };
};

void InteractPacket::write(BinaryStream& stream)
{
    stream.writeByte(static_cast<uint8_t>(this->action));
    BinaryStream::serialize<ActorRuntimeId>::write(this->actorRuntimeId, stream);

    if (this->action == InteractPacket::Action::InteractUpdate
        || this->action == InteractPacket::Action::StopRiding)
    {
        stream.writeVec3(this->position);
    };
};