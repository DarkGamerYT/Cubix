#include "SubChunk.hpp"
SubChunk::SubChunk()
{

};

void SubChunk::serialize(BinaryStream& stream, const bool isNetwork)
{
    // https://gist.github.com/Tomcc/a96af509e275b1af483b25c543cfbf37

    stream.writeByte(static_cast<uint8_t>(SharedConstants::CurrentSubChunkFormat));
    stream.writeByte(static_cast<uint8_t>(this->mLayers.size())); // Storage count

    stream.writeSignedByte(this->mIndex);
    for (BlockStorage& storage : this->mLayers)
        storage.serialize(stream, isNetwork);
};