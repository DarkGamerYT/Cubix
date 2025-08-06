#include "Chunk.hpp"
Chunk::Chunk()
    : mSubChunks(24)
{
    SubChunk subChunk;
    subChunk.mIndex = -4;

    BlockStorage storage;
    for (double x = 0; x < 16; x++)
        for (double z = 0; z < 16; z++)
        {
            storage.setBlock(Vec3{ x, 0, z }, BlockRegistry::STONE);
            storage.setBlock(Vec3{ x, 1, z }, BlockRegistry::COBBLESTONE);
            storage.setBlock(Vec3{ x, 2, z }, BlockRegistry::DIRT);
        };

    subChunk.mLayers.emplace_back(storage);
    this->mSubChunks[0] = subChunk;
};

void Chunk::serialize(BinaryStream& stream, const bool isNetwork)
{
    for (SubChunk& subChunk : this->mSubChunks)
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