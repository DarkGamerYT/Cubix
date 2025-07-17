#pragma once
#include "../world/item/ItemGroup.hpp"
#include "BlockRegistry.hpp"

class ItemGroupRegistry
{
public:
    // Construction
    static inline ItemGroup PLANKS = { ItemCategory::Construction, "itemGroup.name.planks" };
    static inline ItemGroup WALLS = { ItemCategory::Construction, "itemGroup.name.walls" };
    static inline ItemGroup FENCE = { ItemCategory::Construction, "itemGroup.name.fence" };
    static inline ItemGroup FENCE_GATE = { ItemCategory::Construction, "itemGroup.name.fenceGate" };
    static inline ItemGroup STAIRS = { ItemCategory::Construction, "itemGroup.name.stairs" };
    static inline ItemGroup DOORS = { ItemCategory::Construction, "itemGroup.name.door" };
    static inline ItemGroup TRAPDOOR = { ItemCategory::Construction, "itemGroup.name.trapdoor" };
    static inline ItemGroup CONSTRUCTION_EMPTY_1 = { ItemCategory::Construction };
    static inline ItemGroup GLASS = { ItemCategory::Construction, "itemGroup.name.glass" };
    static inline ItemGroup GLASS_PANE = { ItemCategory::Construction, "itemGroup.name.glassPane" };
    static inline ItemGroup CONSTRUCTION_EMPTY_2 = { ItemCategory::Construction };
    static inline ItemGroup SLAB = { ItemCategory::Construction, "itemGroup.name.slab" };
    static inline ItemGroup STONEBRICK = { ItemCategory::Construction, "itemGroup.name.stoneBrick" };
    static inline ItemGroup CONSTRUCTION_EMPTY_3 = { ItemCategory::Construction };
    static inline ItemGroup SANDSTONE = { ItemCategory::Construction, "itemGroup.name.sandstone" };
    static inline ItemGroup CONSTRUCTION_EMPTY_4 = { ItemCategory::Construction };
    static inline ItemGroup COPPER = { ItemCategory::Construction, "itemGroup.name.copper" };
    static inline ItemGroup CONSTRUCTION_EMPTY_5 = { ItemCategory::Construction };
    static inline ItemGroup WOOL = { ItemCategory::Construction, "itemGroup.name.wool" };
    static inline ItemGroup WOOL_CARPET = { ItemCategory::Construction, "itemGroup.name.woolCarpet" };
    static inline ItemGroup CONCRETE_POWDER = { ItemCategory::Construction, "itemGroup.name.concretePowder" };
    static inline ItemGroup CONCRETE = { ItemCategory::Construction, "itemGroup.name.concrete" };
    static inline ItemGroup STAINED_CLAY = { ItemCategory::Construction, "itemGroup.name.stainedClay" };
    static inline ItemGroup GLAZED_TERRACOTTA = { ItemCategory::Construction, "itemGroup.name.glazedTerracotta" };
    static inline ItemGroup CONSTRUCTION_EMPTY_6 = { ItemCategory::Construction };

    // Nature
    static inline ItemGroup NATURE_EMPTY_1 = { ItemCategory::Nature };
    static inline ItemGroup ORE = { ItemCategory::Nature, "itemGroup.name.ore" };
    static inline ItemGroup STONE = { ItemCategory::Nature, "itemGroup.name.stone" };
    static inline ItemGroup NATURE_EMPTY_2 = { ItemCategory::Nature };
    static inline ItemGroup LOG = { ItemCategory::Nature, "itemGroup.name.log" };
    static inline ItemGroup WOOD = { ItemCategory::Nature, "itemGroup.name.wood" };
    static inline ItemGroup LEAVES = { ItemCategory::Nature, "itemGroup.name.leaves" };
    static inline ItemGroup SAPLING = { ItemCategory::Nature, "itemGroup.name.sapling" };
    static inline ItemGroup NATURE_EMPTY_3 = { ItemCategory::Nature };
    static inline ItemGroup SEED = { ItemCategory::Nature, "itemGroup.name.seed" };
    static inline ItemGroup CROP = { ItemCategory::Nature, "itemGroup.name.crop" };
    static inline ItemGroup NATURE_EMPTY_4 = { ItemCategory::Nature };
    static inline ItemGroup GRASS = { ItemCategory::Nature, "itemGroup.name.grass" };
    static inline ItemGroup CORAL = { ItemCategory::Nature, "itemGroup.name.coral_decorations" };
    static inline ItemGroup FLOWER = { ItemCategory::Nature, "itemGroup.name.flower" };
    static inline ItemGroup DYE = { ItemCategory::Nature, "itemGroup.name.dye" };
    static inline ItemGroup NATURE_EMPTY_5 = { ItemCategory::Nature };
    static inline ItemGroup RAW_FOOD = { ItemCategory::Nature, "itemGroup.name.rawFood" };
    static inline ItemGroup MUSHROOM = { ItemCategory::Nature, "itemGroup.name.mushroom" };
    static inline ItemGroup NATURE_EMPTY_6 = { ItemCategory::Nature };
    static inline ItemGroup MONSTER_STONE = { ItemCategory::Nature, "itemGroup.name.monsterStoneEgg" };
    static inline ItemGroup NATURE_EMPTY_7 = { ItemCategory::Nature };
    static inline ItemGroup MOB_EGGS = { ItemCategory::Nature, "itemGroup.name.mobEgg" };
    static inline ItemGroup NATURE_EMPTY_8 = { ItemCategory::Nature };
    static inline ItemGroup CORAL_BLOCKS = { ItemCategory::Nature, "itemGroup.name.coral" };
    static inline ItemGroup SCULK = { ItemCategory::Nature, "itemGroup.name.sculk" };
    static inline ItemGroup NATURE_EMPTY_9 = { ItemCategory::Nature };

    // Equipment
    static inline ItemGroup HELMET = { ItemCategory::Equipment, "itemGroup.name.helmet" };
    static inline ItemGroup CHESTPLATE = { ItemCategory::Equipment, "itemGroup.name.chestplate" };
    static inline ItemGroup LEGGINGS = { ItemCategory::Equipment, "itemGroup.name.leggings" };
    static inline ItemGroup BOOTS = { ItemCategory::Equipment, "itemGroup.name.boots" };
    static inline ItemGroup SWORD = { ItemCategory::Equipment, "itemGroup.name.sword" };
    static inline ItemGroup AXE = { ItemCategory::Equipment, "itemGroup.name.axe" };
    static inline ItemGroup PICKAXE = { ItemCategory::Equipment, "itemGroup.name.pickaxe" };
    static inline ItemGroup SHOVEL = { ItemCategory::Equipment, "itemGroup.name.shovel" };
    static inline ItemGroup HOE = { ItemCategory::Equipment, "itemGroup.name.hoe" };
    static inline ItemGroup EQUIPMENT_EMPTY_1 = { ItemCategory::Equipment };
    static inline ItemGroup ARROW = { ItemCategory::Equipment, "itemGroup.name.arrow" };
    static inline ItemGroup EQUIPMENT_EMPTY_2 = { ItemCategory::Equipment };
    static inline ItemGroup COOKED_FOOD = { ItemCategory::Equipment, "itemGroup.name.cookedFood" };
    static inline ItemGroup MISC_FOOD = { ItemCategory::Equipment, "itemGroup.name.miscFood" };
    static inline ItemGroup EQUIPMENT_EMPTY_3 = { ItemCategory::Equipment };
    static inline ItemGroup GOAT_HORN = { ItemCategory::Equipment, "itemGroup.name.goatHorn" };
    static inline ItemGroup EQUIPMENT_EMPTY_4 = { ItemCategory::Equipment };
    static inline ItemGroup BUNDLES = { ItemCategory::Equipment, "itemGroup.name.bundles" };
    static inline ItemGroup HORSE_ARMOR = { ItemCategory::Equipment, "itemGroup.name.horseArmor" };
    static inline ItemGroup EQUIPMENT_EMPTY_5 = { ItemCategory::Equipment };
    static inline ItemGroup POTION = { ItemCategory::Equipment, "itemGroup.name.potion" };
    static inline ItemGroup SPLASH_POTION = { ItemCategory::Equipment, "itemGroup.name.splashPotion" };
    static inline ItemGroup LINGERING_POTION = { ItemCategory::Equipment, "itemGroup.name.lingeringPotion" };
    static inline ItemGroup OMINOUS_BOTTLE = { ItemCategory::Equipment, "itemGroup.name.ominousBottle" };
    static inline ItemGroup EQUIPMENT_EMPTY_6 = { ItemCategory::Equipment };

    // Items
    static inline ItemGroup ITEMS_EMPTY_1 = { ItemCategory::Items };
    static inline ItemGroup BED = { ItemCategory::Items, "itemGroup.name.bed" };
    static inline ItemGroup ITEMS_EMPTY_2 = { ItemCategory::Items };
    static inline ItemGroup CANDLES = { ItemCategory::Items, "itemGroup.name.candles" };
    static inline ItemGroup ITEMS_EMPTY_3 = { ItemCategory::Items };
    static inline ItemGroup ANVIL = { ItemCategory::Items, "itemGroup.name.anvil" };
    static inline ItemGroup ITEMS_EMPTY_4 = { ItemCategory::Items };
    static inline ItemGroup CHEST = { ItemCategory::Items, "itemGroup.name.chest" };
    static inline ItemGroup ITEMS_EMPTY_5 = { ItemCategory::Items };
    static inline ItemGroup SHULKER_BOX = { ItemCategory::Items, "itemGroup.name.shulkerBox" };
    static inline ItemGroup ITEMS_EMPTY_6 = { ItemCategory::Items };
    static inline ItemGroup RECORD = { ItemCategory::Items, "itemGroup.name.record" };
    static inline ItemGroup ITEMS_EMPTY_7 = { ItemCategory::Items };
    static inline ItemGroup SIGN = { ItemCategory::Items, "itemGroup.name.sign" };
    static inline ItemGroup HANGING_SIGN = { ItemCategory::Items, "itemGroup.name.hanging_sign" };
    static inline ItemGroup ITEMS_EMPTY_8 = { ItemCategory::Items };
    static inline ItemGroup SKULL = { ItemCategory::Items, "itemGroup.name.skull" };
    static inline ItemGroup ITEMS_EMPTY_9 = { ItemCategory::Items };
    static inline ItemGroup ENCHANTED_BOOK = { ItemCategory::Items, "itemGroup.name.enchantedBook" };
    static inline ItemGroup BOAT = { ItemCategory::Items, "itemGroup.name.boat" };
    static inline ItemGroup CHESTBOAT = { ItemCategory::Items, "itemGroup.name.chestboat" };
    static inline ItemGroup RAIL = { ItemCategory::Items, "itemGroup.name.rail" };
    static inline ItemGroup MINECART = { ItemCategory::Items, "itemGroup.name.minecart" };
    static inline ItemGroup ITEMS_EMPTY_10 = { ItemCategory::Items };
    static inline ItemGroup BUTTONS = { ItemCategory::Items, "itemGroup.name.buttons" };
    static inline ItemGroup ITEMS_EMPTY_11 = { ItemCategory::Items };
    static inline ItemGroup PRESSURE_PLATE = { ItemCategory::Items, "itemGroup.name.pressurePlate" };
    static inline ItemGroup ITEMS_EMPTY_12 = { ItemCategory::Items };
    static inline ItemGroup BANNER = { ItemCategory::Items, "itemGroup.name.banner" };
    static inline ItemGroup BANNER_PATTERN = { ItemCategory::Items, "itemGroup.name.banner_pattern" };
    static inline ItemGroup POTTERY_SHERDS = { ItemCategory::Items, "itemGroup.name.potterySherds" };
    static inline ItemGroup SMITHING_TEMPLATE = { ItemCategory::Items, "itemGroup.name.smithing_templates" };
    static inline ItemGroup FIREWORK = { ItemCategory::Items, "itemGroup.name.firework" };
    static inline ItemGroup FIREWORK_STARS = { ItemCategory::Items, "itemGroup.name.fireworkStars" };
    static inline ItemGroup ITEMS_EMPTY_13 = { ItemCategory::Items };

private:
    static inline std::vector<ItemGroup> s_Groups = {};

public:
    static void initialize()
    {
        // Construction
        ItemGroupRegistry::registerGroup(PLANKS
            .setIcon(BlockRegistry::OAK_PLANKS.getBlockItem())
            .add(BlockRegistry::OAK_PLANKS.getBlockItem())
            .add(BlockRegistry::SPRUCE_PLANKS.getBlockItem())
            .add(BlockRegistry::BIRCH_PLANKS.getBlockItem())
            .add(BlockRegistry::JUNGLE_PLANKS.getBlockItem())
            .add(BlockRegistry::ACACIA_PLANKS.getBlockItem())
            .add(BlockRegistry::DARK_OAK_PLANKS.getBlockItem())
            .add(BlockRegistry::MANGROVE_PLANKS.getBlockItem())
            .add(BlockRegistry::CHERRY_PLANKS.getBlockItem())
            .add(BlockRegistry::PALE_OAK_PLANKS.getBlockItem())
            .add(BlockRegistry::BAMBOO_PLANKS.getBlockItem())
            .add(BlockRegistry::BAMBOO_MOSAIC.getBlockItem())
            .add(BlockRegistry::CRIMSON_PLANKS.getBlockItem())
            .add(BlockRegistry::WARPED_PLANKS.getBlockItem()));
        ItemGroupRegistry::registerGroup(WALLS);
        ItemGroupRegistry::registerGroup(FENCE);
        ItemGroupRegistry::registerGroup(FENCE_GATE);
        ItemGroupRegistry::registerGroup(STAIRS);
        ItemGroupRegistry::registerGroup(DOORS);
        ItemGroupRegistry::registerGroup(TRAPDOOR);
        ItemGroupRegistry::registerGroup(CONSTRUCTION_EMPTY_1);
        ItemGroupRegistry::registerGroup(GLASS);
        ItemGroupRegistry::registerGroup(GLASS_PANE);
        ItemGroupRegistry::registerGroup(CONSTRUCTION_EMPTY_2);
        ItemGroupRegistry::registerGroup(SLAB);
        ItemGroupRegistry::registerGroup(STONEBRICK);
        ItemGroupRegistry::registerGroup(CONSTRUCTION_EMPTY_3
            .add(BlockRegistry::COBBLESTONE.getBlockItem()));
        ItemGroupRegistry::registerGroup(SANDSTONE);
        ItemGroupRegistry::registerGroup(CONSTRUCTION_EMPTY_4);
        ItemGroupRegistry::registerGroup(COPPER);
        ItemGroupRegistry::registerGroup(CONSTRUCTION_EMPTY_5);
        ItemGroupRegistry::registerGroup(WOOL);
        ItemGroupRegistry::registerGroup(WOOL_CARPET);
        ItemGroupRegistry::registerGroup(CONCRETE_POWDER);
        ItemGroupRegistry::registerGroup(CONCRETE);
        ItemGroupRegistry::registerGroup(STAINED_CLAY);
        ItemGroupRegistry::registerGroup(GLAZED_TERRACOTTA);
        ItemGroupRegistry::registerGroup(CONSTRUCTION_EMPTY_6);

        // Nature
        ItemGroupRegistry::registerGroup(NATURE_EMPTY_1
            .add(BlockRegistry::GRASS_BLOCK.getBlockItem())
            .add(BlockRegistry::DIRT.getBlockItem()));
        ItemGroupRegistry::registerGroup(ORE);
        ItemGroupRegistry::registerGroup(STONE
            .setIcon(BlockRegistry::STONE.getBlockItem())
            .add(BlockRegistry::STONE.getBlockItem()));
        ItemGroupRegistry::registerGroup(NATURE_EMPTY_2);
        ItemGroupRegistry::registerGroup(LOG
            .add(BlockRegistry::OAK_LOG.getBlockItem()));
        ItemGroupRegistry::registerGroup(WOOD);
        ItemGroupRegistry::registerGroup(LEAVES);
        ItemGroupRegistry::registerGroup(SAPLING);
        ItemGroupRegistry::registerGroup(NATURE_EMPTY_3);
        ItemGroupRegistry::registerGroup(SEED);
        ItemGroupRegistry::registerGroup(CROP
            .add(ItemRegistry::GLOW_BERRIES));
        ItemGroupRegistry::registerGroup(NATURE_EMPTY_4);
        ItemGroupRegistry::registerGroup(GRASS);
        ItemGroupRegistry::registerGroup(CORAL);
        ItemGroupRegistry::registerGroup(FLOWER);
        ItemGroupRegistry::registerGroup(DYE);
        ItemGroupRegistry::registerGroup(NATURE_EMPTY_5);
        ItemGroupRegistry::registerGroup(RAW_FOOD);
        ItemGroupRegistry::registerGroup(MUSHROOM);
        ItemGroupRegistry::registerGroup(NATURE_EMPTY_6);
        ItemGroupRegistry::registerGroup(MONSTER_STONE);
        ItemGroupRegistry::registerGroup(NATURE_EMPTY_7);
        ItemGroupRegistry::registerGroup(MOB_EGGS);
        ItemGroupRegistry::registerGroup(NATURE_EMPTY_8);
        ItemGroupRegistry::registerGroup(CORAL_BLOCKS);
        ItemGroupRegistry::registerGroup(SCULK);
        ItemGroupRegistry::registerGroup(NATURE_EMPTY_9);

        // Equipment
        ItemGroupRegistry::registerGroup(HELMET);
        ItemGroupRegistry::registerGroup(CHESTPLATE);
        ItemGroupRegistry::registerGroup(LEGGINGS);
        ItemGroupRegistry::registerGroup(BOOTS);
        ItemGroupRegistry::registerGroup(SWORD);
        ItemGroupRegistry::registerGroup(AXE);
        ItemGroupRegistry::registerGroup(PICKAXE);
        ItemGroupRegistry::registerGroup(SHOVEL);
        ItemGroupRegistry::registerGroup(HOE);
        ItemGroupRegistry::registerGroup(EQUIPMENT_EMPTY_1);
        ItemGroupRegistry::registerGroup(ARROW);
        ItemGroupRegistry::registerGroup(EQUIPMENT_EMPTY_2);
        ItemGroupRegistry::registerGroup(COOKED_FOOD);
        ItemGroupRegistry::registerGroup(MISC_FOOD);
        ItemGroupRegistry::registerGroup(EQUIPMENT_EMPTY_3);
        ItemGroupRegistry::registerGroup(GOAT_HORN);
        ItemGroupRegistry::registerGroup(EQUIPMENT_EMPTY_4);
        ItemGroupRegistry::registerGroup(BUNDLES);
        ItemGroupRegistry::registerGroup(HORSE_ARMOR);
        ItemGroupRegistry::registerGroup(EQUIPMENT_EMPTY_5);
        ItemGroupRegistry::registerGroup(POTION);
        ItemGroupRegistry::registerGroup(SPLASH_POTION);
        ItemGroupRegistry::registerGroup(LINGERING_POTION);
        ItemGroupRegistry::registerGroup(OMINOUS_BOTTLE);
        ItemGroupRegistry::registerGroup(EQUIPMENT_EMPTY_6);

        // Items
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_1);
        ItemGroupRegistry::registerGroup(BED);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_2);
        ItemGroupRegistry::registerGroup(CANDLES);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_3);
        ItemGroupRegistry::registerGroup(ANVIL);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_4);
        ItemGroupRegistry::registerGroup(CHEST);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_5);
        ItemGroupRegistry::registerGroup(SHULKER_BOX);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_6);
        ItemGroupRegistry::registerGroup(RECORD);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_7);
        ItemGroupRegistry::registerGroup(SIGN);
        ItemGroupRegistry::registerGroup(HANGING_SIGN);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_8);
        ItemGroupRegistry::registerGroup(SKULL);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_9);
        ItemGroupRegistry::registerGroup(ENCHANTED_BOOK);
        ItemGroupRegistry::registerGroup(BOAT
            .add(ItemRegistry::ACACIA_BOAT));
        ItemGroupRegistry::registerGroup(CHESTBOAT);
        ItemGroupRegistry::registerGroup(RAIL);
        ItemGroupRegistry::registerGroup(MINECART);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_10);
        ItemGroupRegistry::registerGroup(BUTTONS);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_11);
        ItemGroupRegistry::registerGroup(PRESSURE_PLATE);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_12);
        ItemGroupRegistry::registerGroup(BANNER);
        ItemGroupRegistry::registerGroup(BANNER_PATTERN);
        ItemGroupRegistry::registerGroup(POTTERY_SHERDS);
        ItemGroupRegistry::registerGroup(SMITHING_TEMPLATE);
        ItemGroupRegistry::registerGroup(FIREWORK);
        ItemGroupRegistry::registerGroup(FIREWORK_STARS);
        ItemGroupRegistry::registerGroup(ITEMS_EMPTY_13);
    };

    static void registerGroup(ItemGroup& group) {
        ItemGroupRegistry::s_Groups.emplace_back(group);
        ItemGroupRegistry::updateIndexCounter();
    };

    static const std::vector<ItemGroup>& getAll() { return ItemGroupRegistry::s_Groups; };

private:
    static void updateIndexCounter()
    {
        if (ItemGroupRegistry::s_Groups.empty())
            return;

        const ItemGroup& lastGroup = ItemGroupRegistry::s_Groups.back();
        groupIndexCounter = lastGroup.getIndex();
    };
};