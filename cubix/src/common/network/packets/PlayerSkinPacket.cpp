#include "PlayerSkinPacket.hpp"
void PlayerSkinPacket::read(BinaryStream& stream)
{
    this->uuid = stream.readUUID();
    this->skin.read(stream);
    this->newSkinName = stream.readString();
    this->oldSkinName = stream.readString();
    this->isMarketplaceContent = stream.readBoolean();
};

void PlayerSkinPacket::write(BinaryStream& stream)
{
    stream.writeUUID(this->uuid);
    this->skin.write(stream);
    stream.writeString(this->newSkinName);
    stream.writeString(this->oldSkinName);
    stream.writeBoolean(this->isMarketplaceContent);
};