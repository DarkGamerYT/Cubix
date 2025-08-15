#include "SetHudPacket.hpp"
void SetHudPacket::read(BinaryStream& stream)
{
    const uint32_t size = stream.readUnsignedVarInt();
    for (uint32_t i = 0; i < size; i++)
        this->elements.emplace_back(static_cast<HudElement>(stream.readSignedVarInt()));
    this->isVisible = stream.readSignedVarInt() == 1;
};

void SetHudPacket::write(BinaryStream& stream)
{
    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->elements.size()));
    for (const HudElement element : this->elements)
        stream.writeSignedVarInt(static_cast<int32_t>(element));
    stream.writeSignedVarInt(this->isVisible);
};