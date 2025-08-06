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
    static ItemGroup CONSTRUCTION_EMPTY_1; // Empty Group
    static ItemGroup GLASS;
    static ItemGroup GLASS_PANE;
    static ItemGroup CONSTRUCTION_EMPTY_2; // Empty Group
    static ItemGroup SLAB;
    static ItemGroup STONEBRICK;
    static ItemGroup CONSTRUCTION_EMPTY_3; // Empty Group
    static ItemGroup SANDSTONE;
    static ItemGroup CONSTRUCTION_EMPTY_4; // Empty Group
    static ItemGroup COPPER;
    static ItemGroup CONSTRUCTION_EMPTY_5; // Empty Group
    static ItemGroup WOOL;
    static ItemGroup WOOL_CARPET;
    static ItemGroup CONCRETE_POWDER;
    static ItemGroup CONCRETE;
    static ItemGroup STAINED_CLAY;
    static ItemGroup GLAZED_TERRACOTTA;
    static ItemGroup CONSTRUCTION_EMPTY_6; // Empty Group

    // Nature
    static ItemGroup NATURE_EMPTY_1; // Empty Group
    static ItemGroup ORE;
    static ItemGroup STONE;
    static ItemGroup NATURE_EMPTY_2; // Empty Group
    static ItemGroup LOG;
    static ItemGroup WOOD;
    static ItemGroup LEAVES;
    static ItemGroup SAPLING;
    static ItemGroup NATURE_EMPTY_3; // Empty Group
    static ItemGroup SEED;
    static ItemGroup CROP;
    static ItemGroup NATURE_EMPTY_4; // Empty Group
    static ItemGroup GRASS;
    static ItemGroup CORAL;
    static ItemGroup FLOWER;
    static ItemGroup DYE;
    static ItemGroup NATURE_EMPTY_5; // Empty Group
    static ItemGroup RAW_FOOD;
    static ItemGroup MUSHROOM;
    static ItemGroup NATURE_EMPTY_6; // Empty Group
    static ItemGroup MONSTER_STONE;
    static ItemGroup NATURE_EMPTY_7; // Empty Group
    static ItemGroup MOB_EGGS;
    static ItemGroup NATURE_EMPTY_8; // Empty Group
    static ItemGroup CORAL_BLOCKS;
    static ItemGroup SCULK;
    static ItemGroup NATURE_EMPTY_9; // Empty Group

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
    static ItemGroup EQUIPMENT_EMPTY_1; // Empty Group
    static ItemGroup ARROW;
    static ItemGroup EQUIPMENT_EMPTY_2; // Empty Group
    static ItemGroup COOKED_FOOD;
    static ItemGroup MISC_FOOD;
    static ItemGroup EQUIPMENT_EMPTY_3; // Empty Group
    static ItemGroup GOAT_HORN;
    static ItemGroup EQUIPMENT_EMPTY_4; // Empty Group
    static ItemGroup BUNDLES;
    static ItemGroup HORSE_ARMOR;
    static ItemGroup EQUIPMENT_EMPTY_5; // Empty Group
    static ItemGroup POTION;
    static ItemGroup SPLASH_POTION;
    static ItemGroup LINGERING_POTION;
    static ItemGroup OMINOUS_BOTTLE;
    static ItemGroup EQUIPMENT_EMPTY_6; // Empty Group

    // Items
    static ItemGroup ITEMS_EMPTY_1; // Empty Group
    static ItemGroup BED;
    static ItemGroup ITEMS_EMPTY_2; // Empty Group
    static ItemGroup CANDLES;
    static ItemGroup ITEMS_EMPTY_3; // Empty Group
    static ItemGroup ANVIL;
    static ItemGroup ITEMS_EMPTY_4; // Empty Group
    static ItemGroup CHEST;
    static ItemGroup ITEMS_EMPTY_5; // Empty Group
    static ItemGroup SHULKER_BOX;
    static ItemGroup ITEMS_EMPTY_6; // Empty Group
    static ItemGroup RECORD;
    static ItemGroup ITEMS_EMPTY_7; // Empty Group
    static ItemGroup SIGN;
    static ItemGroup HANGING_SIGN;
    static ItemGroup ITEMS_EMPTY_8; // Empty Group
    static ItemGroup SKULL;
    static ItemGroup ITEMS_EMPTY_9; // Empty Group
    static ItemGroup ENCHANTED_BOOK;
    static ItemGroup BOAT;
    static ItemGroup CHESTBOAT;
    static ItemGroup RAIL;
    static ItemGroup MINECART;
    static ItemGroup ITEMS_EMPTY_10; // Empty Group
    static ItemGroup BUTTONS;
    static ItemGroup ITEMS_EMPTY_11; // Empty Group
    static ItemGroup PRESSURE_PLATE;
    static ItemGroup ITEMS_EMPTY_12; // Empty Group
    static ItemGroup BANNER;
    static ItemGroup BANNER_PATTERN;
    static ItemGroup POTTERY_SHERDS;
    static ItemGroup SMITHING_TEMPLATE;
    static ItemGroup FIREWORK;
    static ItemGroup FIREWORK_STARS;
    static ItemGroup ITEMS_EMPTY_13; // Empty Group
};

#endif // !ITEMGROUPREGISTRY_HPP