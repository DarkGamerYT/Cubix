#include "NetworkChunkPublisherUpdatePacket.hpp"
void NetworkChunkPublisherUpdatePacket::read(BinaryStream& stream)
{
    this->position = stream.readBlockPosition();
    this->radius = stream.readUnsignedVarInt();

    int32_t size = stream.readInt();
    for (int32_t i = 0; i < size; i++)
        this->savedChunks.emplace_back(stream.readChunkPos());
};

void NetworkChunkPublisherUpdatePacket::write(BinaryStream& stream)
{
    stream.writeBlockPosition(this->position);
    stream.writeUnsignedVarInt(this->radius);

    stream.writeInt(static_cast<int32_t>(this->savedChunks.size()));
    //stream.writeUnsignedVarInt(static_cast<uint32_t>(this->savedChunks.size()));
    for (const auto& pos : this->savedChunks)
        stream.writeChunkPos(pos);
};