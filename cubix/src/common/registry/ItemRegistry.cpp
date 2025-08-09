#include "ItemRegistry.hpp"

void ItemRegistry::initialize()
{
    ItemRegistry::registerItem(AIR.setMaxStackSize(255));

    ItemRegistry::registerItem(ACACIA_BOAT);
    ItemRegistry::registerItem(GLOW_BERRIES.setVersion(ItemVersion::Legacy));
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