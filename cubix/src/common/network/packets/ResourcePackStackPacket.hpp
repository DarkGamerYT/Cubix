#pragma once
#include "../Packet.hpp"

#include "../../world/level/storage/Experiments.hpp"

struct Addon
{
    std::string packId;
    std::string packVersion;
    std::string subPackName;
};

struct TexturePack
{
    std::string packId;
    std::string packVersion;
    std::string subPackName;
};

class ResourcePackStackPacket final : public Packet
{
public:
    bool texturePackRequired = false;
    std::vector<Addon> addons;
    std::vector<TexturePack> texturePacks;
    std::string baseGameVersion;
    Experiments experiments;
    bool includeEditorPacks = false;

public:
    ResourcePackStackPacket()
        : Packet(
            "ResourcePackStackPacket",
            MinecraftPacketIds::ResourcePackStack) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};