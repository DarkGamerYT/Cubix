#include "ItemGroupRegistry.hpp"
void ItemGroupRegistry::initialize()
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

void ItemGroupRegistry::updateIndexCounter()
{
    if (ItemGroupRegistry::sGroups.empty())
        return;

    const ItemGroup& lastGroup = ItemGroupRegistry::sGroups.back();
    groupIndexCounter = lastGroup.getIndex();
};

// Construction
ItemGroup ItemGroupRegistry::PLANKS { ItemCategory::Construction, "itemGroup.name.planks" };
ItemGroup ItemGroupRegistry::WALLS { ItemCategory::Construction, "itemGroup.name.walls" };
ItemGroup ItemGroupRegistry::FENCE { ItemCategory::Construction, "itemGroup.name.fence" };
ItemGroup ItemGroupRegistry::FENCE_GATE { ItemCategory::Construction, "itemGroup.name.fenceGate" };
ItemGroup ItemGroupRegistry::STAIRS { ItemCategory::Construction, "itemGroup.name.stairs" };
ItemGroup ItemGroupRegistry::DOORS { ItemCategory::Construction, "itemGroup.name.door" };
ItemGroup ItemGroupRegistry::TRAPDOOR { ItemCategory::Construction, "itemGroup.name.trapdoor" };
ItemGroup ItemGroupRegistry::CONSTRUCTION_EMPTY_1 { ItemCategory::Construction }; // Empty Group
ItemGroup ItemGroupRegistry::GLASS { ItemCategory::Construction, "itemGroup.name.glass" };
ItemGroup ItemGroupRegistry::GLASS_PANE { ItemCategory::Construction, "itemGroup.name.glassPane" };
ItemGroup ItemGroupRegistry::CONSTRUCTION_EMPTY_2 { ItemCategory::Construction }; // Empty Group
ItemGroup ItemGroupRegistry::SLAB { ItemCategory::Construction, "itemGroup.name.slab" };
ItemGroup ItemGroupRegistry::STONEBRICK { ItemCategory::Construction, "itemGroup.name.stoneBrick" };
ItemGroup ItemGroupRegistry::CONSTRUCTION_EMPTY_3 { ItemCategory::Construction }; // Empty Group
ItemGroup ItemGroupRegistry::SANDSTONE { ItemCategory::Construction, "itemGroup.name.sandstone" };
ItemGroup ItemGroupRegistry::CONSTRUCTION_EMPTY_4 { ItemCategory::Construction }; // Empty Group
ItemGroup ItemGroupRegistry::COPPER { ItemCategory::Construction, "itemGroup.name.copper" };
ItemGroup ItemGroupRegistry::CONSTRUCTION_EMPTY_5 { ItemCategory::Construction }; // Empty Group
ItemGroup ItemGroupRegistry::WOOL { ItemCategory::Construction, "itemGroup.name.wool" };
ItemGroup ItemGroupRegistry::WOOL_CARPET { ItemCategory::Construction, "itemGroup.name.woolCarpet" };
ItemGroup ItemGroupRegistry::CONCRETE_POWDER { ItemCategory::Construction, "itemGroup.name.concretePowder" };
ItemGroup ItemGroupRegistry::CONCRETE { ItemCategory::Construction, "itemGroup.name.concrete" };
ItemGroup ItemGroupRegistry::STAINED_CLAY { ItemCategory::Construction, "itemGroup.name.stainedClay" };
ItemGroup ItemGroupRegistry::GLAZED_TERRACOTTA { ItemCategory::Construction, "itemGroup.name.glazedTerracotta" };
ItemGroup ItemGroupRegistry::CONSTRUCTION_EMPTY_6 { ItemCategory::Construction }; // Empty Group

// Nature
ItemGroup ItemGroupRegistry::NATURE_EMPTY_1 { ItemCategory::Nature }; // Empty Group
ItemGroup ItemGroupRegistry::ORE { ItemCategory::Nature, "itemGroup.name.ore" };
ItemGroup ItemGroupRegistry::STONE { ItemCategory::Nature, "itemGroup.name.stone" };
ItemGroup ItemGroupRegistry::NATURE_EMPTY_2 { ItemCategory::Nature }; // Empty Group
ItemGroup ItemGroupRegistry::LOG { ItemCategory::Nature, "itemGroup.name.log" };
ItemGroup ItemGroupRegistry::WOOD { ItemCategory::Nature, "itemGroup.name.wood" };
ItemGroup ItemGroupRegistry::LEAVES { ItemCategory::Nature, "itemGroup.name.leaves" };
ItemGroup ItemGroupRegistry::SAPLING { ItemCategory::Nature, "itemGroup.name.sapling" };
ItemGroup ItemGroupRegistry::NATURE_EMPTY_3 { ItemCategory::Nature }; // Empty Group
ItemGroup ItemGroupRegistry::SEED { ItemCategory::Nature, "itemGroup.name.seed" };
ItemGroup ItemGroupRegistry::CROP { ItemCategory::Nature, "itemGroup.name.crop" };
ItemGroup ItemGroupRegistry::NATURE_EMPTY_4 { ItemCategory::Nature }; // Empty Group
ItemGroup ItemGroupRegistry::GRASS { ItemCategory::Nature, "itemGroup.name.grass" };
ItemGroup ItemGroupRegistry::CORAL { ItemCategory::Nature, "itemGroup.name.coral_decorations" };
ItemGroup ItemGroupRegistry::FLOWER { ItemCategory::Nature, "itemGroup.name.flower" };
ItemGroup ItemGroupRegistry::DYE { ItemCategory::Nature, "itemGroup.name.dye" };
ItemGroup ItemGroupRegistry::NATURE_EMPTY_5 { ItemCategory::Nature }; // Empty Group
ItemGroup ItemGroupRegistry::RAW_FOOD { ItemCategory::Nature, "itemGroup.name.rawFood" };
ItemGroup ItemGroupRegistry::MUSHROOM { ItemCategory::Nature, "itemGroup.name.mushroom" };
ItemGroup ItemGroupRegistry::NATURE_EMPTY_6 { ItemCategory::Nature }; // Empty Group
ItemGroup ItemGroupRegistry::MONSTER_STONE { ItemCategory::Nature, "itemGroup.name.monsterStoneEgg" };
ItemGroup ItemGroupRegistry::NATURE_EMPTY_7 { ItemCategory::Nature }; // Empty Group
ItemGroup ItemGroupRegistry::MOB_EGGS { ItemCategory::Nature, "itemGroup.name.mobEgg" };
ItemGroup ItemGroupRegistry::NATURE_EMPTY_8 { ItemCategory::Nature }; // Empty Group
ItemGroup ItemGroupRegistry::CORAL_BLOCKS { ItemCategory::Nature, "itemGroup.name.coral" };
ItemGroup ItemGroupRegistry::SCULK { ItemCategory::Nature, "itemGroup.name.sculk" };
ItemGroup ItemGroupRegistry::NATURE_EMPTY_9 { ItemCategory::Nature }; // Empty Group

// Equipment
ItemGroup ItemGroupRegistry::HELMET { ItemCategory::Equipment, "itemGroup.name.helmet" };
ItemGroup ItemGroupRegistry::CHESTPLATE { ItemCategory::Equipment, "itemGroup.name.chestplate" };
ItemGroup ItemGroupRegistry::LEGGINGS { ItemCategory::Equipment, "itemGroup.name.leggings" };
ItemGroup ItemGroupRegistry::BOOTS { ItemCategory::Equipment, "itemGroup.name.boots" };
ItemGroup ItemGroupRegistry::SWORD { ItemCategory::Equipment, "itemGroup.name.sword" };
ItemGroup ItemGroupRegistry::AXE { ItemCategory::Equipment, "itemGroup.name.axe" };
ItemGroup ItemGroupRegistry::PICKAXE { ItemCategory::Equipment, "itemGroup.name.pickaxe" };
ItemGroup ItemGroupRegistry::SHOVEL { ItemCategory::Equipment, "itemGroup.name.shovel" };
ItemGroup ItemGroupRegistry::HOE { ItemCategory::Equipment, "itemGroup.name.hoe" };
ItemGroup ItemGroupRegistry::EQUIPMENT_EMPTY_1 { ItemCategory::Equipment }; // Empty Group
ItemGroup ItemGroupRegistry::ARROW { ItemCategory::Equipment, "itemGroup.name.arrow" };
ItemGroup ItemGroupRegistry::EQUIPMENT_EMPTY_2 { ItemCategory::Equipment }; // Empty Group
ItemGroup ItemGroupRegistry::COOKED_FOOD { ItemCategory::Equipment, "itemGroup.name.cookedFood" };
ItemGroup ItemGroupRegistry::MISC_FOOD { ItemCategory::Equipment, "itemGroup.name.miscFood" };
ItemGroup ItemGroupRegistry::EQUIPMENT_EMPTY_3 { ItemCategory::Equipment }; // Empty Group
ItemGroup ItemGroupRegistry::GOAT_HORN { ItemCategory::Equipment, "itemGroup.name.goatHorn" };
ItemGroup ItemGroupRegistry::EQUIPMENT_EMPTY_4 { ItemCategory::Equipment }; // Empty Group
ItemGroup ItemGroupRegistry::BUNDLES { ItemCategory::Equipment, "itemGroup.name.bundles" };
ItemGroup ItemGroupRegistry::HORSE_ARMOR { ItemCategory::Equipment, "itemGroup.name.horseArmor" };
ItemGroup ItemGroupRegistry::EQUIPMENT_EMPTY_5 { ItemCategory::Equipment }; // Empty Group
ItemGroup ItemGroupRegistry::POTION { ItemCategory::Equipment, "itemGroup.name.potion" };
ItemGroup ItemGroupRegistry::SPLASH_POTION { ItemCategory::Equipment, "itemGroup.name.splashPotion" };
ItemGroup ItemGroupRegistry::LINGERING_POTION { ItemCategory::Equipment, "itemGroup.name.lingeringPotion" };
ItemGroup ItemGroupRegistry::OMINOUS_BOTTLE { ItemCategory::Equipment, "itemGroup.name.ominousBottle" };
ItemGroup ItemGroupRegistry::EQUIPMENT_EMPTY_6 { ItemCategory::Equipment }; // Empty Group

// Items
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_1 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::BED { ItemCategory::Items, "itemGroup.name.bed" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_2 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::CANDLES { ItemCategory::Items, "itemGroup.name.candles" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_3 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::ANVIL { ItemCategory::Items, "itemGroup.name.anvil" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_4 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::CHEST { ItemCategory::Items, "itemGroup.name.chest" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_5 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::SHULKER_BOX { ItemCategory::Items, "itemGroup.name.shulkerBox" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_6 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::RECORD { ItemCategory::Items, "itemGroup.name.record" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_7 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::SIGN { ItemCategory::Items, "itemGroup.name.sign" };
ItemGroup ItemGroupRegistry::HANGING_SIGN { ItemCategory::Items, "itemGroup.name.hanging_sign" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_8 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::SKULL { ItemCategory::Items, "itemGroup.name.skull" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_9 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::ENCHANTED_BOOK { ItemCategory::Items, "itemGroup.name.enchantedBook" };
ItemGroup ItemGroupRegistry::BOAT { ItemCategory::Items, "itemGroup.name.boat" };
ItemGroup ItemGroupRegistry::CHESTBOAT { ItemCategory::Items, "itemGroup.name.chestboat" };
ItemGroup ItemGroupRegistry::RAIL { ItemCategory::Items, "itemGroup.name.rail" };
ItemGroup ItemGroupRegistry::MINECART { ItemCategory::Items, "itemGroup.name.minecart" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_10 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::BUTTONS { ItemCategory::Items, "itemGroup.name.buttons" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_11 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::PRESSURE_PLATE { ItemCategory::Items, "itemGroup.name.pressurePlate" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_12 { ItemCategory::Items }; // Empty Group
ItemGroup ItemGroupRegistry::BANNER { ItemCategory::Items, "itemGroup.name.banner" };
ItemGroup ItemGroupRegistry::BANNER_PATTERN { ItemCategory::Items, "itemGroup.name.banner_pattern" };
ItemGroup ItemGroupRegistry::POTTERY_SHERDS { ItemCategory::Items, "itemGroup.name.potterySherds" };
ItemGroup ItemGroupRegistry::SMITHING_TEMPLATE { ItemCategory::Items, "itemGroup.name.smithing_templates" };
ItemGroup ItemGroupRegistry::FIREWORK { ItemCategory::Items, "itemGroup.name.firework" };
ItemGroup ItemGroupRegistry::FIREWORK_STARS { ItemCategory::Items, "itemGroup.name.fireworkStars" };
ItemGroup ItemGroupRegistry::ITEMS_EMPTY_13 { ItemCategory::Items }; // Empty Group