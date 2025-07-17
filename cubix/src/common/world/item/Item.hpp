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
    ItemVersion m_Version = ItemVersion::None;
    std::string m_Identifier;
    int32_t m_NetId = 0; // Invalid item
    int32_t m_BlockId = 0; // Invalid block
    uint8_t m_StackSize = 1;
    uint8_t m_MaxStackSize = 64;
    uint16_t m_MaxDamage = 0;
    Rarity m_Rarity = Rarity::Common;

    std::vector<std::string> m_CanPlaceOn;
    std::vector<std::string> m_CanBreak;

    bool m_IsHiddenInCommands = false;
    ItemGroup m_CreativeGroup = Item::defaultCreativeGroup(*this);

public:
    Item() : m_Identifier("minecraft:invalid") {};
    Item(const std::string& identifier)
        : m_Identifier(identifier), m_NetId(itemNetIdCounter++) {};
    Item(const std::string& identifier, int id)
        : m_Identifier(identifier), m_NetId(id) {};

    const std::string& getIdentifier() const { return this->m_Identifier; };
    int32_t getNetworkId() const { return this->m_NetId; };
    int32_t getBlockId() const { return this->m_BlockId; };
    ItemVersion getParseVersion() const { return this->m_Version; };

    ItemGroup getCreativeGroup() const { return this->m_CreativeGroup; };
    uint8_t getStackSize() const { return this->m_StackSize; };
    uint8_t getMaxStackSize() const { return this->m_MaxStackSize; };
    int16_t getMaxDamage() const { return this->m_MaxDamage; };

    const std::vector<std::string>& getCanPlaceOn() const { return this->m_CanPlaceOn; };
    const std::vector<std::string>& getCanBreak() const { return this->m_CanBreak; };


    Item& setCreativeGroup(const ItemGroup& group) { this->m_CreativeGroup = group; return *this; };
    Item& setStackSize(uint8_t size) { this->m_StackSize = size; return *this; };
    Item& setMaxStackSize(uint8_t size) { this->m_MaxStackSize = size; return *this; };
    Item& setMaxDamage(int maxDamage) { this->m_MaxDamage = maxDamage; return *this; };

    Item& setVersion(ItemVersion version) { this->m_Version = version; return *this; };
    Item& setBlockId(const Block& block) { this->m_BlockId = block.getNetworkId(); return *this; };


    std::unique_ptr<Nbt::CompoundTag> buildNetworkTag() const;

    bool operator==(Item const& other) const {
        return this->m_NetId == other.m_NetId
            && this->m_Identifier == other.m_Identifier;
    };

private:
    static ItemGroup& defaultCreativeGroup(Item&);
};

#endif // !ITEM_HPP