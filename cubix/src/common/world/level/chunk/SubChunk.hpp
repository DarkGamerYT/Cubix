#ifndef SUBCHUNK_HPP
#define SUBCHUNK_HPP

#include "../../../SharedConstants.hpp"
#include "../../../util/BinaryStream.hpp"

#include "../storage/BlockStorage.hpp"

class SubChunk
{
public:
    int8_t mIndex;
    std::vector<BlockStorage> mLayers;

public:
    SubChunk();

    int8_t getIndex() const { return this->mIndex; };

    bool isEmpty() const { return this->mLayers.empty(); };
    const std::vector<BlockStorage>& getLayers() const { return this->mLayers; };

    void serialize(BinaryStream& stream, bool isNetwork = false);
};

#endif // !SUBCHUNK_HPP