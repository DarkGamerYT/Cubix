#pragma once
#include "../Packet.hpp"

enum class ResourcePackResponse
{
    Cancel                    = 1,
    Downloading               = 2,
    DownloadingFinished       = 3,
    ResourcePackStackFinished = 4
};

class ResourcePackClientResponsePacket final : public Packet
{
public:
    ResourcePackResponse responseStatus;
    std::vector<std::string> packIds;

public:
    ResourcePackClientResponsePacket()
        : Packet(
            "ResourcePackClientResponsePacket",
            MinecraftPacketIds::ResourcePackClientResponse) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};