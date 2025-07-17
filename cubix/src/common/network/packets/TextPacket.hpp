#pragma once
#include "../Packet.hpp"

enum class TextType
{
    Raw = 0,
    Chat,
    Translate,
    Popup,
    JukeboxPopup,
    Tip,
    SystemMessage,
    Whisper,
    Announcement,
    TextObjectWhisper,
    TextObject,
    TextObjectAnnouncement
};

class TextPacket : public Packet
{
public:
    TextType type;
    bool isLocalized;
    std::string source;
    std::string message;
    std::vector<std::string> parameters;
    std::string xuid;
    std::string platformId;
    std::string filteredMessage;

public:
    TextPacket()
        : Packet("TextPacket", MinecraftPacketIds::Text) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};