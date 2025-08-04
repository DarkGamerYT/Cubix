#pragma once
#include "../Packet.hpp"

class ServerboundLoadingScreenPacket final : public Packet
{
public:
    bool isEnd = false;
    std::optional<uint32_t> screenId;

public:
    ServerboundLoadingScreenPacket()
        : Packet(
            "ServerboundLoadingScreenPacket",
            MinecraftPacketIds::ServerboundLoadingScreenPacket) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};