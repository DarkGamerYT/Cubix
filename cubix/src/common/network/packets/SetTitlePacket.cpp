#include "SetTitlePacket.hpp"
void SetTitlePacket::read(BinaryStream& stream)
{
    this->type = (TitleType)stream.readSignedVarInt();
    this->text = stream.readString<Endianness::NetworkEndian>();
    this->fadeInTime = stream.readSignedVarInt();
    this->stayTime = stream.readSignedVarInt();
    this->fadeOutTime = stream.readSignedVarInt();
    this->xuid = stream.readString<Endianness::NetworkEndian>();
    this->platformOnlineId = stream.readString<Endianness::NetworkEndian>();
    this->filteredMessage = stream.readString<Endianness::NetworkEndian>();
};

void SetTitlePacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt((int)this->type);
    stream.writeString<Endianness::NetworkEndian>(this->text);
    stream.writeSignedVarInt(this->fadeInTime);
    stream.writeSignedVarInt(this->stayTime);
    stream.writeSignedVarInt(this->fadeOutTime);
    stream.writeString<Endianness::NetworkEndian>(this->xuid);
    stream.writeString<Endianness::NetworkEndian>(this->platformOnlineId);
    stream.writeString<Endianness::NetworkEndian>(this->filteredMessage);
};