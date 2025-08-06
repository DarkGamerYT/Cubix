#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "../../../util/BinaryStream.hpp"

#include "SubChunk.hpp"

class Chunk
{
private:
    std::vector<SubChunk> mSubChunks;

public:
    Chunk();

    const std::vector<SubChunk>& getSubChunks() const { return this->mSubChunks; };

    void serialize(BinaryStream& stream, bool isNetwork = false);
};

#endif // !CHUNK_HPP