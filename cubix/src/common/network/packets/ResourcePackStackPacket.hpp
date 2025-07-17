#pragma once
#include "../Packet.hpp"
#include "./types/Experiments.hpp"

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

class ResourcePackStackPacket : public Packet
{
public:
    bool texturePackRequired;
    std::vector<Addon> addons;
    std::vector<TexturePack> texturePacks;
    std::string baseGameVersion;
    Experiments experiments;
    bool includeEditorPacks;

public:
    ResourcePackStackPacket()
        : Packet(
            "ResourcePackStackPacket",
            MinecraftPacketIds::ResourcePackStack) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};