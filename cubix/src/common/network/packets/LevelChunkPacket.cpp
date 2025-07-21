#include "LevelChunkPacket.hpp"
void LevelChunkPacket::read(BinaryStream& stream)
{
    this->chunkPosition = stream.readChunkPos();

    this->dimensionId = stream.readSignedVarInt();
    if (!this->requestSubChunks) {
        this->subChunkCount = stream.readUnsignedVarInt();
    }
    else if (this->subChunkLimit < 0) {
        stream.readUnsignedVarInt();
    }
    else {
        stream.readUnsignedVarInt();
        this->subChunkLimit = stream.readUnsignedShort();
    };

    this->cacheEnabled = stream.readBoolean();
    if (this->cacheEnabled) {
        uint32_t blobIdsSize = stream.readUnsignedVarInt();
        for (uint32_t i = 0; i < blobIdsSize; i++)
            this->blobIds.emplace_back(stream.readUnsignedLong());
    };

    const uint32_t length = stream.readUnsignedVarInt();
    const uint8_t* ptr = stream.readBytes(length);

    std::vector<uint8_t> buffer(length);
    std::memcpy(buffer.data(), ptr, length);

    this->chunkData = buffer;
};

void LevelChunkPacket::write(BinaryStream& stream)
{
    stream.writeChunkPos(this->chunkPosition);

    stream.writeSignedVarInt(this->dimensionId);
    if (!this->requestSubChunks) {
        stream.writeUnsignedVarInt(this->subChunkCount);
    }
    else if (this->subChunkLimit < 0) {
        stream.writeUnsignedVarInt(-1);
    }
    else {
        stream.writeUnsignedVarInt(0xFFFFFFFE);
        stream.writeUnsignedShort(this->subChunkLimit);
    };

    stream.writeBoolean(this->cacheEnabled);
    if (this->cacheEnabled) {
        stream.writeUnsignedVarInt(static_cast<uint32_t>(this->blobIds.size()));
        for (const uint64_t blobId : this->blobIds)
            stream.writeUnsignedLong(blobId);
    };

    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->chunkData.size()));
    stream.writeBytes(this->chunkData.data(), this->chunkData.size());
};