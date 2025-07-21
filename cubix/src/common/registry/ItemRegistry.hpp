#ifndef ITEMREGISTRY_HPP
#define ITEMREGISTRY_HPP

#include <ranges>

#include "../world/item/Item.hpp"

class ItemRegistry
{
public:
    static inline Item INVALID; // Invalid Item

    static inline Item AIR = Item{ "minecraft:air", -158 }.setMaxStackSize(255);

    static inline Item ACACIA_BOAT = { "minecraft:acacia_boat", 405 };
    static inline Item GLOW_BERRIES = Item{ "minecraft:glow_berries", 796 }.setVersion(ItemVersion::Legacy);

private:
    static inline std::vector<std::pair<std::string, Item>> s_Items = {};

public:
    static void initialize()
    {
        ItemRegistry::registerItem(AIR);

        ItemRegistry::registerItem(ACACIA_BOAT);
        ItemRegistry::registerItem(GLOW_BERRIES);
    };

    static void registerItem(const Item& item) {
        ItemRegistry::s_Items.emplace_back(item.getIdentifier(), item);
        ItemRegistry::updateNetworkIdCounter();
    };

    static std::vector<Item> getAll() {
        std::vector<Item> items;
        items.reserve(s_Items.size());

        for (const auto& item : s_Items | std::views::values)
            items.emplace_back(item);

        return items;
    };

private:
    static void updateNetworkIdCounter()
    {
        if (ItemRegistry::s_Items.empty())
            return;
            
        const auto& [ identifier, item ] = ItemRegistry::s_Items.back();
        itemNetIdCounter = item.getNetworkId();
    };
};

#endif // !ITEMREGISTRY_HPP