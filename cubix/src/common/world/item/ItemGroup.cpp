#include "ItemGroup.hpp"
#include "../../registry/ItemRegistry.hpp"
Item& ItemGroup::defaultIcon() {
    return ItemRegistry::INVALID;
};