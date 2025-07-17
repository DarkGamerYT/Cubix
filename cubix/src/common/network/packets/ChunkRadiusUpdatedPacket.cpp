#include "ChunkRadiusUpdatedPacket.hpp"
void ChunkRadiusUpdatedPacket::read(BinaryStream& stream)
{
    this->chunkRadius = stream.readSignedVarInt();
};

void ChunkRadiusUpdatedPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(this->chunkRadius);
};