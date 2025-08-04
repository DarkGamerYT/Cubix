#pragma once
#include "../Packet.hpp"
#include "../../util/UUID.hpp"

struct ResourcePack {
    Util::UUID packId;
    std::string packVersion;
    long packSize;
    std::string contentKey;
    std::string subPackName;
    std::string contentIdentity;
    bool hasScripts;
    bool isAddonPack;
    bool isRayTracingCapable;
    std::string cdnUrl;
};

class ResourcePacksInfoPacket final : public Packet
{
public:
    bool resourcePackRequired = false;
    bool hasAddonPacks = false;
    bool hasScripts = false;
    bool forceDisableVibrantVisuals = false;

    Util::UUID worldTemplateId;
    std::string worldTemplateVersion;

    std::vector<ResourcePack> resourcePacks;

public:
    ResourcePacksInfoPacket()
        : Packet(
            "ResourcePacksInfoPacket",
            MinecraftPacketIds::ResourcePacksInfo) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};