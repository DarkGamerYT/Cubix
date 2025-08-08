#include "ItemStackRequestData.hpp"
ItemStackRequestData BinaryStream::serialize<ItemStackRequestData>::read(BinaryStream& stream) {
    ItemStackRequestData itemStackRequestData{};

    itemStackRequestData.mRequestId = stream.readSignedVarInt();
    {
        const uint32_t size = stream.readUnsignedVarInt();
        for (uint32_t i = 0; i < size; ++i)
        {
            itemStackRequestData.mActions.emplace_back(
                BinaryStream::serialize<ItemStackRequestAction>::read(stream));
        };
    };

    {
        const uint32_t size = stream.readUnsignedVarInt();
        for (uint32_t i = 0; i < size; ++i)
            itemStackRequestData.mStringsToFilter.emplace_back(stream.readString<Endianness::NetworkEndian>());
    };

    itemStackRequestData.mStringsOrigin = static_cast<TextProcessingEventOrigin>(stream.readInt());
    return itemStackRequestData;
};

void BinaryStream::serialize<ItemStackRequestData>::write(const ItemStackRequestData& value, BinaryStream& stream) {

};