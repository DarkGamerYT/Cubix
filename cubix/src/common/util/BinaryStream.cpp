#include "BinaryStream.hpp"
#include "../nbt/NbtIo.hpp"
void BinaryStream::writeItem(const std::shared_ptr<Item>& item, const bool includeNetId)
{
    this->writeSignedVarInt(item->getNetworkId());
    this->writeUnsignedShort(item->getStackSize());
    this->writeUnsignedVarInt(item->getMaxDamage());

    if (true == includeNetId)
        this->writeSignedVarInt(item->getNetworkId());

    this->writeSignedVarInt(item->getBlockId());

    BinaryStream dataBuffer;
    dataBuffer.writeShort(-1);
    dataBuffer.writeByte(1);

    const Nbt::CompoundTag tag;
    Nbt::write<Endianness::NetworkEndian>(dataBuffer, tag.copy());

    for (const std::string& value : item->getCanPlaceOn())
        dataBuffer.writeString<Endianness::NetworkEndian>(value);

    for (const std::string& value : item->getCanBreak())
        dataBuffer.writeString<Endianness::NetworkEndian>(value);


    const size_t streamSize = dataBuffer.size();
    this->writeUnsignedVarInt(streamSize);
    this->writeBytes(dataBuffer.data(), streamSize);
};