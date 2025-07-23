#include "ItemRegistry.hpp"

void ItemRegistry::initialize()
{
    ItemRegistry::registerItem(AIR);

    ItemRegistry::registerItem(ACACIA_BOAT);
    ItemRegistry::registerItem(GLOW_BERRIES);
};

std::vector<Item> ItemRegistry::getAll() {
    std::vector<Item> items;
    items.reserve(sItems.size());

    for (const auto& item : sItems | std::views::values)
        items.emplace_back(item);

    return items;
};

void ItemRegistry::updateNetworkIdCounter()
{
    if (ItemRegistry::sItems.empty())
        return;

    const auto& [ identifier, item ] = ItemRegistry::sItems.back();
    itemNetIdCounter = item.getNetworkId();
};

// Items
Item ItemRegistry::AIR = Item{ "minecraft:air", -158 }.setMaxStackSize(255);

Item ItemRegistry::ACACIA_BOAT = { "minecraft:acacia_boat", 405 };
Item ItemRegistry::GLOW_BERRIES = Item{ "minecraft:glow_berries", 796 }.setVersion(ItemVersion::Legacy);