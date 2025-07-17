#include "ResourcePackStackPacket.hpp"
void ResourcePackStackPacket::read(BinaryStream& stream)
{
    
};

void ResourcePackStackPacket::write(BinaryStream& stream)
{
    stream.writeBoolean(this->texturePackRequired);

    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->addons.size()));
    for (Addon entry : this->addons)
    {
        stream.writeString(entry.packId);
        stream.writeString(entry.packVersion);
        stream.writeString(entry.subPackName);
    };

    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->texturePacks.size()));
    for (TexturePack entry : this->texturePacks)
    {
        stream.writeString(entry.packId);
        stream.writeString(entry.packVersion);
        stream.writeString(entry.subPackName);
    };

    stream.writeString(this->baseGameVersion);

    stream.writeUnsignedInt(static_cast<uint32_t>(this->experiments.list.size()));
    for (Experiment entry : this->experiments.list)
    {
        stream.writeString(entry.toggleName);
        stream.writeBoolean(entry.enabled);
    };
    stream.writeBoolean(this->experiments.experimentsEverEnabled);

    stream.writeBoolean(this->includeEditorPacks);
};