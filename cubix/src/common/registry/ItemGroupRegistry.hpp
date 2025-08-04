#ifndef ITEMGROUPREGISTRY_HPP
#define ITEMGROUPREGISTRY_HPP

#include "../world/item/ItemGroup.hpp"
#include "BlockRegistry.hpp"

class ItemGroupRegistry
{
public:
    static void initialize();

    static void registerGroup(ItemGroup& group) {
        ItemGroupRegistry::sGroups.emplace_back(group);
        ItemGroupRegistry::updateIndexCounter();
    };

    static const std::vector<ItemGroup>& getAll() { return sGroups; };

private:
    static inline std::vector<ItemGroup> sGroups{};

    static void updateIndexCounter();

public:
    // Construction
    static ItemGroup PLANKS;
    static ItemGroup WALLS;
    static ItemGroup FENCE;
    static ItemGroup FENCE_GATE;
    static ItemGroup STAIRS;
    static ItemGroup DOORS;
    static ItemGroup TRAPDOOR;
    static inline ItemGroup CONSTRUCTION_EMPTY_1 { ItemCategory::Construction };
    static ItemGroup GLASS;
    static ItemGroup GLASS_PANE;
    static inline ItemGroup CONSTRUCTION_EMPTY_2 { ItemCategory::Construction };
    static ItemGroup SLAB;
    static ItemGroup STONEBRICK;
    static inline ItemGroup CONSTRUCTION_EMPTY_3 { ItemCategory::Construction };
    static ItemGroup SANDSTONE;
    static inline ItemGroup CONSTRUCTION_EMPTY_4 { ItemCategory::Construction };
    static ItemGroup COPPER;
    static inline ItemGroup CONSTRUCTION_EMPTY_5 = { ItemCategory::Construction };
    static ItemGroup WOOL;
    static ItemGroup WOOL_CARPET;
    static ItemGroup CONCRETE_POWDER;
    static ItemGroup CONCRETE;
    static ItemGroup STAINED_CLAY;
    static ItemGroup GLAZED_TERRACOTTA;
    static inline ItemGroup CONSTRUCTION_EMPTY_6 { ItemCategory::Construction };

    // Nature
    static inline ItemGroup NATURE_EMPTY_1 { ItemCategory::Nature };
    static ItemGroup ORE;
    static ItemGroup STONE;
    static inline ItemGroup NATURE_EMPTY_2 { ItemCategory::Nature };
    static ItemGroup LOG;
    static ItemGroup WOOD;
    static ItemGroup LEAVES;
    static ItemGroup SAPLING;
    static inline ItemGroup NATURE_EMPTY_3 = { ItemCategory::Nature };
    static ItemGroup SEED;
    static ItemGroup CROP;
    static inline ItemGroup NATURE_EMPTY_4 { ItemCategory::Nature };
    static ItemGroup GRASS;
    static ItemGroup CORAL;
    static ItemGroup FLOWER;
    static ItemGroup DYE;
    static inline ItemGroup NATURE_EMPTY_5 { ItemCategory::Nature };
    static ItemGroup RAW_FOOD;
    static ItemGroup MUSHROOM;
    static inline ItemGroup NATURE_EMPTY_6 { ItemCategory::Nature };
    static ItemGroup MONSTER_STONE;
    static inline ItemGroup NATURE_EMPTY_7 { ItemCategory::Nature };
    static ItemGroup MOB_EGGS;
    static inline ItemGroup NATURE_EMPTY_8 { ItemCategory::Nature };
    static ItemGroup CORAL_BLOCKS;
    static ItemGroup SCULK;
    static inline ItemGroup NATURE_EMPTY_9 { ItemCategory::Nature };

    // Equipment
    static ItemGroup HELMET;
    static ItemGroup CHESTPLATE;
    static ItemGroup LEGGINGS;
    static ItemGroup BOOTS;
    static ItemGroup SWORD;
    static ItemGroup AXE;
    static ItemGroup PICKAXE;
    static ItemGroup SHOVEL;
    static ItemGroup HOE;
    static inline ItemGroup EQUIPMENT_EMPTY_1 { ItemCategory::Equipment };
    static ItemGroup ARROW;
    static inline ItemGroup EQUIPMENT_EMPTY_2 { ItemCategory::Equipment };
    static ItemGroup COOKED_FOOD;
    static ItemGroup MISC_FOOD;
    static inline ItemGroup EQUIPMENT_EMPTY_3 { ItemCategory::Equipment };
    static ItemGroup GOAT_HORN;
    static inline ItemGroup EQUIPMENT_EMPTY_4 { ItemCategory::Equipment };
    static ItemGroup BUNDLES;
    static ItemGroup HORSE_ARMOR;
    static inline ItemGroup EQUIPMENT_EMPTY_5 { ItemCategory::Equipment };
    static ItemGroup POTION;
    static ItemGroup SPLASH_POTION;
    static ItemGroup LINGERING_POTION;
    static ItemGroup OMINOUS_BOTTLE;
    static inline ItemGroup EQUIPMENT_EMPTY_6 { ItemCategory::Equipment };

    // Items
    static inline ItemGroup ITEMS_EMPTY_1 { ItemCategory::Items };
    static ItemGroup BED;
    static inline ItemGroup ITEMS_EMPTY_2 { ItemCategory::Items };
    static ItemGroup CANDLES;
    static inline ItemGroup ITEMS_EMPTY_3 { ItemCategory::Items };
    static ItemGroup ANVIL;
    static inline ItemGroup ITEMS_EMPTY_4 { ItemCategory::Items };
    static ItemGroup CHEST;
    static inline ItemGroup ITEMS_EMPTY_5 { ItemCategory::Items };
    static ItemGroup SHULKER_BOX;
    static inline ItemGroup ITEMS_EMPTY_6 { ItemCategory::Items };
    static ItemGroup RECORD;
    static inline ItemGroup ITEMS_EMPTY_7 { ItemCategory::Items };
    static ItemGroup SIGN;
    static ItemGroup HANGING_SIGN;
    static inline ItemGroup ITEMS_EMPTY_8 { ItemCategory::Items };
    static ItemGroup SKULL;
    static inline ItemGroup ITEMS_EMPTY_9 { ItemCategory::Items };
    static ItemGroup ENCHANTED_BOOK;
    static ItemGroup BOAT;
    static ItemGroup CHESTBOAT;
    static ItemGroup RAIL;
    static ItemGroup MINECART;
    static inline ItemGroup ITEMS_EMPTY_10 { ItemCategory::Items };
    static ItemGroup BUTTONS;
    static inline ItemGroup ITEMS_EMPTY_11 = { ItemCategory::Items };
    static ItemGroup PRESSURE_PLATE;
    static inline ItemGroup ITEMS_EMPTY_12 = { ItemCategory::Items };
    static ItemGroup BANNER;
    static ItemGroup BANNER_PATTERN;
    static ItemGroup POTTERY_SHERDS;
    static ItemGroup SMITHING_TEMPLATE;
    static ItemGroup FIREWORK;
    static ItemGroup FIREWORK_STARS;
    static inline ItemGroup ITEMS_EMPTY_13 { ItemCategory::Items };
};

#endif // !ITEMGROUPREGISTRY_HPP