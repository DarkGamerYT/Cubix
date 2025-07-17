#include "SetTitlePacket.hpp"
void SetTitlePacket::read(BinaryStream& stream)
{
    this->type = (TitleType)stream.readSignedVarInt();
    this->text = stream.readString();
    this->fadeInTime = stream.readSignedVarInt();
    this->stayTime = stream.readSignedVarInt();
    this->fadeOutTime = stream.readSignedVarInt();
    this->xuid = stream.readString();
    this->platformOnlineId = stream.readString();
    this->filteredMessage = stream.readString();
};

void SetTitlePacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt((int)this->type);
    stream.writeString(this->text);
    stream.writeSignedVarInt(this->fadeInTime);
    stream.writeSignedVarInt(this->stayTime);
    stream.writeSignedVarInt(this->fadeOutTime);
    stream.writeString(this->xuid);
    stream.writeString(this->platformOnlineId);
    stream.writeString(this->filteredMessage);
};