#pragma once
#include "../Packet.hpp"

class SetTitlePacket : public Packet
{
public:
    enum class TitleType
    {
        Clear = 0,
        Reset = 1,
        Title = 2,
        Subtitle = 3,
        Actionbar = 4,
        Times = 5,
        TitleTextObject = 6,
        SubtitleTextObject = 7,
        ActionbarTextObject = 8
    };

    TitleType type;
    std::string text;
    int fadeInTime;
    int stayTime;
    int fadeOutTime;
    std::string xuid;
    std::string platformOnlineId;
    std::string filteredMessage;

public:
    SetTitlePacket()
        : Packet("SetTitlePacket", MinecraftPacketIds::SetTitle) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};