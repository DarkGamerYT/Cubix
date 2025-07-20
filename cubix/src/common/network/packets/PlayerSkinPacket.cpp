#include "PlayerSkinPacket.hpp"
void PlayerSkinPacket::read(BinaryStream& stream)
{
    this->uuid = stream.readUUID();
    this->skin.read(stream);
    this->newSkinName = stream.readString<Endianness::NetworkEndian>();
    this->oldSkinName = stream.readString<Endianness::NetworkEndian>();
    this->isMarketplaceContent = stream.readBoolean();
};

void PlayerSkinPacket::write(BinaryStream& stream)
{
    stream.writeUUID(this->uuid);
    this->skin.write(stream);
    stream.writeString<Endianness::NetworkEndian>(this->newSkinName);
    stream.writeString<Endianness::NetworkEndian>(this->oldSkinName);
    stream.writeBoolean(this->isMarketplaceContent);
};