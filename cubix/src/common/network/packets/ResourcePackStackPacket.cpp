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

    const auto& experiments = this->experiments.experimentList;
    stream.writeUnsignedInt(static_cast<uint32_t>(experiments.size()));
    for (const auto& [name, isEnabled] : experiments)
    {
        stream.writeString<Endianness::NetworkEndian>(name);
        stream.writeBoolean(isEnabled);
    };
    stream.writeBoolean(this->experiments.experimentsEverEnabled);

    stream.writeBoolean(this->includeEditorPacks);
};