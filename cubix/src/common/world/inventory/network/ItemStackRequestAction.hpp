#ifndef ITEMSTACKREQUESTACTION_HPP
#define ITEMSTACKREQUESTACTION_HPP

#include <memory>

#include "../../../util/BinaryStream.hpp"

#include "ItemStackRequestActionType.hpp"

class ItemStackRequestAction {
private:
    ItemStackRequestActionType mType;

public:
    explicit ItemStackRequestAction(const ItemStackRequestActionType type)
        : mType(type) {};

};

template <>
struct BinaryStream::serializeTraits<ItemStackRequestAction> {
    using readType = std::unique_ptr<ItemStackRequestAction>;
};

template <>
struct BinaryStream::serialize<ItemStackRequestAction> {
    using traits   = BinaryStream::serializeTraits<ItemStackRequestAction>;
    using readType = traits::readType;

    static readType read(BinaryStream& stream);
    static void write(const ItemStackRequestAction& value, BinaryStream& stream);
};

#endif //ITEMSTACKREQUESTACTION_HPP
