#include "InteractPacket.hpp"
void InteractPacket::read(BinaryStream& stream)
{
    this->action = (InteractPacket::Action)stream.readByte();
    this->targetRuntimeId = stream.readUnsignedVarLong();

    if (this->action == InteractPacket::Action::InteractUpdate
        || this->action == InteractPacket::Action::StopRiding)
    {
        this->position = stream.readVec3();
    };
};

void InteractPacket::write(BinaryStream& stream)
{
    stream.writeByte((uint8_t)this->action);
    stream.writeUnsignedVarLong(this->targetRuntimeId);

    if (this->action == InteractPacket::Action::InteractUpdate
        || this->action == InteractPacket::Action::StopRiding)
    {
        stream.writeVec3(this->position);
    };
};