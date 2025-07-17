#ifndef SUBCHUNK_HPP
#define SUBCHUNK_HPP

#include "../../../SharedConstants.hpp"
#include "../../../util/BinaryStream.hpp"

#include "../storage/BlockStorage.hpp"

class SubChunk
{
public:
    int8_t m_Index;
    std::vector<BlockStorage> m_Layers;

public:
    SubChunk();

    void serialize(BinaryStream& stream, bool isNetwork = false);
};

#endif // !SUBCHUNK_HPP