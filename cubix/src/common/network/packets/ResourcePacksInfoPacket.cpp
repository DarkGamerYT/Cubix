#include "ResourcePacksInfoPacket.hpp"
void ResourcePacksInfoPacket::read(BinaryStream& stream)
{
    this->resourcePackRequired = stream.readBoolean();
    this->hasAddonPacks = stream.readBoolean();
    this->hasScripts = stream.readBoolean();
    this->forceDisableVibrantVisuals = stream.readBoolean();

    this->worldTemplateId = stream.readUUID();
    this->worldTemplateVersion = stream.readString<Endianness::NetworkEndian>();

    unsigned short arraySize = stream.readUnsignedShort();
    for (unsigned short i = 0; i < arraySize; i++)
    {
        ResourcePack resourcePack;
        resourcePack.packId = stream.readUUID();
        resourcePack.packVersion = stream.readString<Endianness::NetworkEndian>();
        resourcePack.packSize = stream.readUnsignedVarInt();
        resourcePack.contentKey = stream.readString<Endianness::NetworkEndian>();
        resourcePack.subPackName = stream.readString<Endianness::NetworkEndian>();
        resourcePack.contentIdentity = stream.readString<Endianness::NetworkEndian>();
        resourcePack.hasScripts = stream.readBoolean();
        resourcePack.isRayTracingCapable = stream.readBoolean();
        resourcePack.cdnUrl = stream.readString<Endianness::NetworkEndian>();

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
    stream.writeString<Endianness::NetworkEndian>(this->worldTemplateVersion);

    stream.writeShort((short)this->resourcePacks.size());
    for (const ResourcePack& entry : this->resourcePacks)
    {
        stream.writeUUID(entry.packId);
        stream.writeString<Endianness::NetworkEndian>(entry.packVersion);
        stream.writeUnsignedVarLong(entry.packSize);
        stream.writeString<Endianness::NetworkEndian>(entry.contentKey);
        stream.writeString<Endianness::NetworkEndian>(entry.subPackName);
        stream.writeString<Endianness::NetworkEndian>(entry.contentIdentity);
        stream.writeBoolean(entry.hasScripts);
        stream.writeBoolean(entry.isAddonPack);
        stream.writeBoolean(entry.isRayTracingCapable);
        stream.writeString<Endianness::NetworkEndian>(entry.cdnUrl);
    };
};