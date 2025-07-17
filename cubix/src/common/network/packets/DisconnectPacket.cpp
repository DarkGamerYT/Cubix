#include "DisconnectPacket.hpp"
void DisconnectPacket::read(BinaryStream& stream)
{
    this->reason = (DisconnectReason)stream.readSignedVarInt();
    this->skipMessage = stream.readBoolean();

    if (!this->skipMessage)
        this->message = stream.readString();
};

void DisconnectPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt((int32_t)this->reason);
    stream.writeBoolean(this->skipMessage);

    if (!this->skipMessage)
    {
        stream.writeString(this->message);
        stream.writeString("");
    };
};