#include "TextPacket.hpp"
void TextPacket::read(BinaryStream& stream)
{
    this->type = (TextType)stream.readByte();
    this->isLocalized = stream.readBoolean() || this->type == TextType::Translate;

    switch (this->type)
    {
        case TextType::Chat:
        case TextType::Whisper:
        case TextType::Announcement:
            this->source = stream.readString<Endianness::NetworkEndian>();

        case TextType::Raw:
        case TextType::Tip:
        case TextType::SystemMessage:
        case TextType::TextObjectWhisper:
        case TextType::TextObject:
        case TextType::TextObjectAnnouncement:
            this->message = stream.readString<Endianness::NetworkEndian>();
            break;

        case TextType::Translate:
        case TextType::Popup:
        case TextType::JukeboxPopup:
            this->message = stream.readString<Endianness::NetworkEndian>();

            uint32_t size = stream.readUnsignedVarInt();
            for (uint32_t i = 0; i < size; i++)
                this->parameters.emplace_back(stream.readString<Endianness::NetworkEndian>());
            break;
    };

    this->xuid = stream.readString<Endianness::NetworkEndian>();
    this->platformId = stream.readString<Endianness::NetworkEndian>();
    this->filteredMessage = stream.readString<Endianness::NetworkEndian>();
};

void TextPacket::write(BinaryStream& stream)
{
    stream.writeByte((uint8_t)this->type);
    stream.writeBoolean(this->isLocalized || this->type == TextType::Translate);

    switch (this->type)
    {
        case TextType::Chat:
        case TextType::Whisper:
        case TextType::Announcement:
            stream.writeString<Endianness::NetworkEndian>(this->source);

        case TextType::Raw:
        case TextType::Tip:
        case TextType::SystemMessage:
        case TextType::TextObjectWhisper:
        case TextType::TextObject:
        case TextType::TextObjectAnnouncement:
            stream.writeString<Endianness::NetworkEndian>(this->message);
            break;

        case TextType::Translate:
        case TextType::Popup:
        case TextType::JukeboxPopup:
            stream.writeString<Endianness::NetworkEndian>(this->message);

            stream.writeUnsignedVarInt(static_cast<uint32_t>(this->parameters.size()));
            for (std::string parameter : this->parameters)
                stream.writeString<Endianness::NetworkEndian>(parameter);
            break;
    };

    stream.writeString<Endianness::NetworkEndian>(this->xuid);
    stream.writeString<Endianness::NetworkEndian>(this->platformId);
    stream.writeString<Endianness::NetworkEndian>(this->filteredMessage);
};