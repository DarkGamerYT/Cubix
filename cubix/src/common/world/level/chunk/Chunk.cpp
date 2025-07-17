#include "Chunk.hpp"
Chunk::Chunk()
{
    SubChunk subChunk;
    subChunk.m_Index = -4;

    BlockStorage storage;
    subChunk.m_Layers.emplace_back(storage);

    this->m_SubChunks.emplace_back(subChunk);
};

void Chunk::serialize(BinaryStream& stream, bool isNetwork)
{
    for (SubChunk& subChunk : this->m_SubChunks)
        subChunk.serialize(stream, isNetwork);

    // Biomes?
    for (int index = 0; index < 24; index++)
    {
        stream.writeByte(0);
        stream.writeSignedVarInt(1 << 1);
    };

    // Border blocks?
    stream.writeByte(0);
};