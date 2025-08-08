#ifndef ITEMSTACKREQUESTDATA_HPP
#define ITEMSTACKREQUESTDATA_HPP

#include "../../../network/packets/types/TextProcessingEventOrigin.hpp"
#include "../../../util/BinaryStream.hpp"

#include "ItemStackRequestAction.hpp"

class ItemStackRequestData {
    friend struct BinaryStream::serialize<ItemStackRequestData>;

private:
    int mRequestId;
    std::vector<std::unique_ptr<ItemStackRequestAction>> mActions;
    std::vector<std::string> mStringsToFilter;
    TextProcessingEventOrigin mStringsOrigin;

public:
    ItemStackRequestData() = default;

    int getRequestId() const { return this->mRequestId; };
    const std::vector<std::string>& getStringsToFilter() const { return this->mStringsToFilter; };
    TextProcessingEventOrigin getStringsOrigin() const { return this->mStringsOrigin; };
    const std::vector<std::unique_ptr<ItemStackRequestAction>>&getActions() const { return this->mActions; };
};

template <>
struct BinaryStream::serialize<ItemStackRequestData> {
    static ItemStackRequestData read(BinaryStream& stream);
    static void write(const ItemStackRequestData& value, BinaryStream& stream);
};

#endif //ITEMSTACKREQUESTDATA_HPP
