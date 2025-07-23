#ifndef ITEMREGISTRY_HPP
#define ITEMREGISTRY_HPP

#include <ranges>

#include "../world/item/Item.hpp"

class ItemRegistry
{
public:
    static inline Item INVALID; // Invalid Item

    static Item AIR;

    static Item ACACIA_BOAT;
    static Item GLOW_BERRIES;

private:
    static inline std::vector<std::pair<std::string, Item>> sItems{};

public:
    static void initialize();

    static void registerItem(const Item& item) {
        ItemRegistry::sItems.emplace_back(item.getIdentifier(), item);
        ItemRegistry::updateNetworkIdCounter();
    };

    static std::vector<Item> getAll();

private:
    static void updateNetworkIdCounter();
};

#endif // !ITEMREGISTRY_HPP