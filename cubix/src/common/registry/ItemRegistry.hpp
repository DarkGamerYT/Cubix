#ifndef ITEMREGISTRY_HPP
#define ITEMREGISTRY_HPP

#include <ranges>

#include "../world/item/Item.hpp"

class ItemRegistry
{
public:
    static void initialize();

    static void registerItem(const Item& item) {
        ItemRegistry::sItems.emplace_back(item.getIdentifier(), item);
        ItemRegistry::updateNetworkIdCounter();
    };

    static std::vector<Item> getAll();

private:
    static inline std::vector<std::pair<std::string, Item>> sItems{};

    static void updateNetworkIdCounter();

public:
    static inline Item INVALID; // Invalid Item

    static inline Item AIR { "minecraft:air", -158 };

    static inline Item ACACIA_BOAT { "minecraft:acacia_boat", 405 };
    static inline Item GLOW_BERRIES { "minecraft:glow_berries", 796 };
};

#endif // !ITEMREGISTRY_HPP