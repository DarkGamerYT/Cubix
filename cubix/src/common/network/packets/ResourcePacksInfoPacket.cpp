#include "ResourcePacksInfoPacket.hpp"
void ResourcePacksInfoPacket::read(BinaryStream& stream)
{
    this->resourcePackRequired = stream.readBoolean();
    this->hasAddonPacks = stream.readBoolean();
    this->hasScripts = stream.readBoolean();
    this->forceDisableVibrantVisuals = stream.readBoolean();

    this->worldTemplateId = stream.readUUID();
    this->worldTemplateVersion = stream.readString();

    unsigned short arraySize = stream.readUnsignedShort();
    for (unsigned short i = 0; i < arraySize; i++)
    {
        ResourcePack resourcePack;
        resourcePack.packId = stream.readUUID();
        resourcePack.packVersion = stream.readString();
        resourcePack.packSize = stream.readUnsignedVarInt();
        resourcePack.contentKey = stream.readString();
        resourcePack.subPackName = stream.readString();
        resourcePack.contentIdentity = stream.readString();
        resourcePack.hasScripts = stream.readBoolean();
        resourcePack.isRayTracingCapable = stream.readBoolean();
        resourcePack.cdnUrl = stream.readString();

        this->resourcePacks.emplace_back(resourcePack);
    };
};

void ResourcePacksInfoPacket::write(BinaryStream& stream)
{
    stream.writeBoolean(this->resourcePackRequired);
    stream.writeBoolean(this->hasAddonPacks);
    stream.writeBoolean(this->hasScripts);
    stream.writeBoolean(this->forceDisableVibrantVisuals);

    stream.writeUUID(this->worldTemplateId);
    stream.writeString(this->worldTemplateVersion);

    stream.writeShort((short)this->resourcePacks.size());
    for (const ResourcePack& entry : this->resourcePacks)
    {
        stream.writeUUID(entry.packId);
        stream.writeString(entry.packVersion);
        stream.writeUnsignedVarLong(entry.packSize);
        stream.writeString(entry.contentKey);
        stream.writeString(entry.subPackName);
        stream.writeString(entry.contentIdentity);
        stream.writeBoolean(entry.hasScripts);
        stream.writeBoolean(entry.isAddonPack);
        stream.writeBoolean(entry.isRayTracingCapable);
        stream.writeString(entry.cdnUrl);
    };
};