#include "SubChunk.hpp"
SubChunk::SubChunk()
{
    
};

void SubChunk::serialize(BinaryStream& stream, bool isNetwork)
{
    // https://gist.github.com/Tomcc/a96af509e275b1af483b25c543cfbf37

    stream.writeByte((uint8_t)SharedConstants::CurrentSubChunkFormat);
    stream.writeByte(static_cast<uint8_t>(this->m_Layers.size())); // Storage count

    stream.writeSignedByte(this->m_Index);
    for (BlockStorage& storage : this->m_Layers)
        storage.serialize(stream, isNetwork);
};