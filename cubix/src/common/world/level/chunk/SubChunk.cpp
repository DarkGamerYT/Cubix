#include "SubChunk.hpp"
SubChunk::SubChunk()
{

};

void SubChunk::serialize(BinaryStream& stream, const bool isNetwork)
{
    // https://gist.github.com/Tomcc/a96af509e275b1af483b25c543cfbf37

    stream.writeByte(static_cast<uint8_t>(SharedConstants::CurrentSubChunkFormat));
    stream.writeByte(static_cast<uint8_t>(this->m_layers.size())); // Storage count

    stream.writeSignedByte(this->m_index);
    for (BlockStorage& storage : this->m_layers)
        storage.serialize(stream, isNetwork);
};