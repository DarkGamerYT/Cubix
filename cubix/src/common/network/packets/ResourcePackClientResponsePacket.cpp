#include "ResourcePackClientResponsePacket.hpp"
void ResourcePackClientResponsePacket::read(BinaryStream& stream)
{
    this->responseStatus = (ResourcePackResponse)stream.readByte();

    uint32_t arraySize = stream.readUnsignedVarInt();
    for (uint32_t i = 0; i < arraySize; i++)
        this->packIds.emplace_back(stream.readString());
};

void ResourcePackClientResponsePacket::write(BinaryStream& stream)
{
    stream.writeByte((uint8_t)this->responseStatus);

    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->packIds.size()));
    for (const std::string& packId : this->packIds)
        stream.writeString(packId);
};