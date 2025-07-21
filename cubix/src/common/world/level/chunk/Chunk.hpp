#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "../../../util/BinaryStream.hpp"

#include "SubChunk.hpp"

class Chunk
{
private:
    std::vector<SubChunk> m_subChunks;

public:
    Chunk();

    const std::vector<SubChunk>& getSubChunks() const { return this->m_subChunks; };

    void serialize(BinaryStream& stream, bool isNetwork = false);
};

#endif // !CHUNK_HPP