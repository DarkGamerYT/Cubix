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
            this->source = stream.readString();

        case TextType::Raw:
        case TextType::Tip:
        case TextType::SystemMessage:
        case TextType::TextObjectWhisper:
        case TextType::TextObject:
            this->message = stream.readString();
            break;

        case TextType::Translate:
        case TextType::Popup:
        case TextType::JukeboxPopup:
            this->message = stream.readString();

            uint32_t size = stream.readUnsignedVarInt();
            for (uint32_t i = 0; i < size; i++)
                this->parameters.emplace_back(stream.readString());
            break;
    };

    this->xuid = stream.readString();
    this->platformId = stream.readString();
    this->filteredMessage = stream.readString();
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
            stream.writeString(this->source);

        case TextType::Raw:
        case TextType::Tip:
        case TextType::SystemMessage:
        case TextType::TextObjectWhisper:
        case TextType::TextObject:
            stream.writeString(this->message);
            break;

        case TextType::Translate:
        case TextType::Popup:
        case TextType::JukeboxPopup:
            stream.writeString(this->message);

            stream.writeUnsignedVarInt(static_cast<uint32_t>(this->parameters.size()));
            for (std::string parameter : this->parameters)
                stream.writeString(parameter);
            break;
    };

    stream.writeString(this->xuid);
    stream.writeString(this->platformId);
    stream.writeString(this->filteredMessage);
};