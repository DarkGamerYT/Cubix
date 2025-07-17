#include "RequestChunkRadiusPacket.hpp"
void RequestChunkRadiusPacket::read(BinaryStream& stream)
{
    this->chunkRadius = stream.readSignedVarInt();
    this->maxChunkRadius = stream.readByte();
};

void RequestChunkRadiusPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(this->chunkRadius);
    stream.writeByte(this->maxChunkRadius);
};