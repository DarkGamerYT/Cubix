#include "ItemStackRequestAction.hpp"

BinaryStream::serialize<ItemStackRequestAction>::readType
BinaryStream::serialize<ItemStackRequestAction>::read(BinaryStream& stream) {
    const auto& type = static_cast<ItemStackRequestActionType>(stream.readByte());

    return std::make_unique<ItemStackRequestAction>(type);
};

void BinaryStream::serialize<ItemStackRequestAction>::write(const ItemStackRequestAction& value, BinaryStream& stream) {

};