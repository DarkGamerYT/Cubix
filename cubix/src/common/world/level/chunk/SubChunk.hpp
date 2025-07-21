#ifndef SUBCHUNK_HPP
#define SUBCHUNK_HPP

#include "../../../SharedConstants.hpp"
#include "../../../util/BinaryStream.hpp"

#include "../storage/BlockStorage.hpp"

class SubChunk
{
public:
    int8_t m_index;
    std::vector<BlockStorage> m_layers;

public:
    SubChunk();

    int8_t getIndex() const { return this->m_index; };

    bool isEmpty() const { return this->m_layers.empty(); };
    const std::vector<BlockStorage>& getLayers() const { return this->m_layers; };

    void serialize(BinaryStream& stream, bool isNetwork = false);
};

#endif // !SUBCHUNK_HPP