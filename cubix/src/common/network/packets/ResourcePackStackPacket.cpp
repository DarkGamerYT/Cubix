#include "ResourcePackStackPacket.hpp"
void ResourcePackStackPacket::read(BinaryStream& stream)
{
    
};

void ResourcePackStackPacket::write(BinaryStream& stream)
{
    stream.writeBoolean(this->texturePackRequired);

    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->addons.size()));
    for (const Addon& entry : this->addons)
    {
        stream.writeString<Endianness::NetworkEndian>(entry.packId);
        stream.writeString<Endianness::NetworkEndian>(entry.packVersion);
        stream.writeString<Endianness::NetworkEndian>(entry.subPackName);
    };

    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->texturePacks.size()));
    for (const TexturePack& entry : this->texturePacks)
    {
        stream.writeString<Endianness::NetworkEndian>(entry.packId);
        stream.writeString<Endianness::NetworkEndian>(entry.packVersion);
        stream.writeString<Endianness::NetworkEndian>(entry.subPackName);
    };

    stream.writeString<Endianness::NetworkEndian>(this->baseGameVersion);

    stream.writeUnsignedInt(static_cast<uint32_t>(this->experiments.list.size()));
    for (const Experiment& entry : this->experiments.list)
    {
        stream.writeString<Endianness::NetworkEndian>(entry.toggleName);
        stream.writeBoolean(entry.enabled);
    };
    stream.writeBoolean(this->experiments.experimentsEverEnabled);

    stream.writeBoolean(this->includeEditorPacks);
};