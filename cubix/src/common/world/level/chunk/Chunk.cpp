#include "Chunk.hpp"
Chunk::Chunk()
    : m_subChunks(24)
{
    SubChunk subChunk;
    subChunk.m_index = -4;

    BlockStorage storage;
    for (double x = 0; x < 16; x++)
        for (double z = 0; z < 16; z++)
        {
            storage.setBlock({ x, 0, z }, BlockRegistry::STONE);
            storage.setBlock({ x, 1, z }, BlockRegistry::COBBLESTONE);
            storage.setBlock({ x, 2, z }, BlockRegistry::DIRT);
        };

    subChunk.m_layers.emplace_back(storage);
    this->m_subChunks[0] = subChunk;
};

void Chunk::serialize(BinaryStream& stream, const bool isNetwork)
{
    for (SubChunk& subChunk : this->m_subChunks)
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