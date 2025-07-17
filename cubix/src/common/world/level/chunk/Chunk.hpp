#ifndef CHUNK_HPP
#define CHUNK_HPP

#include "../../../util/BinaryStream.hpp"

#include "SubChunk.hpp"

class Chunk
{
private:
    std::vector<SubChunk> m_SubChunks;

public:
    Chunk();

    void serialize(BinaryStream& stream, bool isNetwork = false);
};

#endif // !CHUNK_HPP