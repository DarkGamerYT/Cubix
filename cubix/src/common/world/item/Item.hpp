#ifndef ITEM_HPP
#define ITEM_HPP

#include <cstdint>
#include <vector>
#include <string>

#include "ItemVersion.hpp"
#include "Rarity.hpp"
#include "ItemGroup.hpp"

#include "../block/Block.hpp"

#include "../../nbt/CompoundTag.hpp"

static uint32_t itemNetIdCounter = 1;
class Item
{
private:
    ItemVersion mVersion = ItemVersion::None;
    std::string mIdentifier;
    int32_t mNetId = 0; // Invalid item
    int32_t mBlockId = 0; // Invalid block
    uint8_t mStackSize = 1;
    uint8_t mMaxStackSize = 64;
    uint16_t mMaxDamage = 0;
    Rarity mRarity = Rarity::Common;

    std::vector<std::string> mCanPlaceOn;
    std::vector<std::string> mCanBreak;

    bool mIsHiddenInCommands = false;
    ItemGroup mCreativeGroup = Item::defaultCreativeGroup(*this);

public:
    Item() : mIdentifier("minecraft:invalid") {};
    Item(const std::string& identifier, const int id)
        : mIdentifier(identifier), mNetId(id) {};
    explicit Item(const std::string& identifier)
        : mIdentifier(identifier), mNetId(itemNetIdCounter++) {};

    const std::string& getIdentifier() const { return this->mIdentifier; };
    int32_t getNetworkId() const { return this->mNetId; };
    int32_t getBlockId() const { return this->mBlockId; };
    ItemVersion getParseVersion() const { return this->mVersion; };

    ItemGroup getCreativeGroup() const { return this->mCreativeGroup; };
    uint8_t getStackSize() const { return this->mStackSize; };
    uint8_t getMaxStackSize() const { return this->mMaxStackSize; };
    int16_t getMaxDamage() const { return this->mMaxDamage; };

    const std::vector<std::string>& getCanPlaceOn() const { return this->mCanPlaceOn; };
    const std::vector<std::string>& getCanBreak() const { return this->mCanBreak; };


    Item& setCreativeGroup(const ItemGroup& group) { this->mCreativeGroup = group; return *this; };
    Item& setStackSize(uint8_t size) { this->mStackSize = size; return *this; };
    Item& setMaxStackSize(uint8_t size) { this->mMaxStackSize = size; return *this; };
    Item& setMaxDamage(const int maxDamage) { this->mMaxDamage = maxDamage; return *this; };

    Item& setVersion(ItemVersion version) { this->mVersion = version; return *this; };
    Item& setBlockId(const Block& block) { this->mBlockId = block.getNetworkId(); return *this; };


    std::unique_ptr<Nbt::CompoundTag> buildNetworkTag() const;

    bool operator==(Item const& other) const {
        return this->mNetId == other.mNetId
            && this->mIdentifier == other.mIdentifier;
    };

private:
    static ItemGroup& defaultCreativeGroup(const Item&);
};

#endif // !ITEM_HPP