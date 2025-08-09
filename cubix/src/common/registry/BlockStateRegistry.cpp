#include "BlockStateRegistry.hpp"
void BlockStateRegistry::initialize()
{
    sStates.emplace_back(ACTIVE);
    sStates.emplace_back(AGE);
    sStates.emplace_back(AGE_BIT);
    {
        std::vector<StateType> stackBits;
        for (int i = 0; i < 64; i++)
            stackBits.emplace_back(i);
        BOOKS_STORED.setPossibleStates(stackBits);
    };
    sStates.emplace_back(BOOKS_STORED);


    {
        std::vector<StateType> vinesAge;
        for (int i = 0; i < 26; i++)
            vinesAge.emplace_back(i);
        TWISTING_VINES_AGE.setPossibleStates(vinesAge);
        WEEPING_VINES_AGE.setPossibleStates(vinesAge);
    };
    sStates.emplace_back(TWISTING_VINES_AGE);
    sStates.emplace_back(WEEPING_VINES_AGE);

    sStates.emplace_back(PILLAR_AXIS);
};

BlockState BlockStateRegistry::ACTIVE { "active", { false, true } };
BlockState BlockStateRegistry::AGE { "age", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } };
BlockState BlockStateRegistry::AGE_BIT { "age_bit", { false, true } };
BlockState BlockStateRegistry::ALLOW_UNDERWATER_BIT { "allow_underwater_bit", { false, true } };
BlockState BlockStateRegistry::ATTACHED_BIT { "attached_bit", { false, true } };
BlockState BlockStateRegistry::ATTACHMENT { "attachment", { "standing", "hanging", "side", "multiple" } };
BlockState BlockStateRegistry::BAMBOO_LEAF_SIZE { "bamboo_leaf_size", { "no_leaves", "small_leaves", "large_leaves" } };
BlockState BlockStateRegistry::BAMBOO_STALK_THICKNESS { "bamboo_stalk_thickness", { "thin", "thick" } };
BlockState BlockStateRegistry::BIG_DRIPLEAF_HEAD { "big_dripleaf_head", { false, true } };
BlockState BlockStateRegistry::BIG_DRIPLEAF_TILT { "big_dripleaf_tilt", { "none", "unstable", "partial_tilt", "full_tilt" } };
BlockState BlockStateRegistry::BITE_COUNTER { "bite_counter", { 0, 1, 2, 3, 4, 5, 6 } };
BlockState BlockStateRegistry::BLOCK_LIGHT_LEVEL { "block_light_level",
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } };
BlockState BlockStateRegistry::BLOOM { "bloom", { false, true } };
BlockState BlockStateRegistry::BOOKS_STORED { "books_stored", {} };
BlockState BlockStateRegistry::BREWINGSTAND_SLOT_A { "brewing_stand_slot_a_bit", { false, true } };
BlockState BlockStateRegistry::BREWINGSTAND_SLOT_B { "brewing_stand_slot_b_bit", { false, true } };
BlockState BlockStateRegistry::BREWINGSTAND_SLOT_C { "brewing_stand_slot_c_bit", { false, true } };
BlockState BlockStateRegistry::BRUSHED_PROGRESS { "brushed_progress", { 0, 1, 2, 3 } };
BlockState BlockStateRegistry::BUTTON_PRESSED_BIT { "button_pressed_bit", { false, true } };
BlockState BlockStateRegistry::CAN_SUMMON { "can_summon", { false, true } };
BlockState BlockStateRegistry::CANDLES { "candles", { 0, 1, 2, 3 } };

BlockState BlockStateRegistry::PERSISTENT_BIT { "persistent_bit", { false, true } };
BlockState BlockStateRegistry::PILLAR_AXIS { "pillar_axis", { "x", "y", "z" } };
BlockState BlockStateRegistry::PORTAL_AXIS { "portal_axis", { "unknown", "x", "z" } };
BlockState BlockStateRegistry::POWERED_BIT { "powered_bit", { false, true } };
BlockState BlockStateRegistry::PRISMARINE_BLOCK_TYPE { "prismarine_block_type", { "default", "dark", "bricks" } };
BlockState BlockStateRegistry::PROPAGULE_STAGE { "propagule_stage", { 0, 1, 2, 3, 4 } };
BlockState BlockStateRegistry::RAIL_DATA_BIT { "rail_data_bit", { false, true } };
BlockState BlockStateRegistry::RAIL_DIRECTION { "rail_direction", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } };
BlockState BlockStateRegistry::REDSTONE_SIGNAL { "redstone_signal",
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } };
BlockState BlockStateRegistry::REPEATER_DELAY { "repeater_delay", { 0, 1, 2, 3 } };
BlockState BlockStateRegistry::RESPAWN_ANCHOR_CHARGE { "respawn_anchor_charge", { 0, 1, 2, 3, 4 } };
BlockState BlockStateRegistry::ROTATION { "rotation", { 0, 1, 2, 3 } };

BlockState BlockStateRegistry::STRIPPED_BIT { "stripped_bit", { false, true } };
BlockState BlockStateRegistry::STRUCTURE_BLOCK_TYPE { "structure_block_type",
    { "data", "save", "load", "corner", "invalid", "export" } };
BlockState BlockStateRegistry::STRUCTURE_VOID_TYPE { "structure_void_type", { "void", "air" } };
BlockState BlockStateRegistry::SUSPENDED_BIT { "suspended_bit", { false, true } };
BlockState BlockStateRegistry::TALL_GRASS_TYPE { "tall_grass_type", { "default", "tall", "fern", "snow" } };
BlockState BlockStateRegistry::TIP { "tip", { false, true } };
BlockState BlockStateRegistry::TOGGLE_BIT { "toggle_bit", { false, true } };
BlockState BlockStateRegistry::TOP_SLOT_BIT { "top_slot_bit", { false, true } };
BlockState BlockStateRegistry::TORCH_FACING_DIRECTION { "torch_facing_direction",
    { "unknown", "west", "east", "north", "south", "top" } };
BlockState BlockStateRegistry::TRIAL_SPAWNER_STATE { "trial_spawner_state", { 0, 1, 2, 3, 4, 5 } };
BlockState BlockStateRegistry::TRIGGERED_BIT { "triggered_bit", { false, true } };
BlockState BlockStateRegistry::TURTLE_EGG_COUNT { "turtle_egg_count", { "one_egg", "two_egg", "three_egg", "four_egg" } };
BlockState BlockStateRegistry::TWISTING_VINES_AGE { "twisting_vines_age", {} };
BlockState BlockStateRegistry::UPDATE_BIT { "update_bit", { false, true } };
BlockState BlockStateRegistry::UPPER_BLOCK_BIT { "upper_block_bit", { false, true } };
BlockState BlockStateRegistry::UPSIDE_DOWN_BIT { "upside_down_bit", { false, true } };
BlockState BlockStateRegistry::VAULT_STATE { "vault_state", { "inactive", "active", "unlocking", "ejecting" } };
BlockState BlockStateRegistry::VINE_DIRECTION { "vine_direction_bits",
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } };
BlockState BlockStateRegistry::WALL_BLOCK_TYPE { "wall_block_type", {
    "cobblestone",
    "mossy_cobblestone",
    "granite",
    "diorite",
    "andesite",
    "sandstone",
    "brick",
    "stone_brick",
    "mossy_stone_brick",
    "nether_brick",
    "end_brick",
    "prismarine",
    "red_sandstone",
    "red_nether_brick"
} };
BlockState BlockStateRegistry::WALL_CONNECTION_TYPE_EAST { "wall_connection_type_east", { "none", "short", "tall" } };
BlockState BlockStateRegistry::WALL_CONNECTION_TYPE_NORTH { "wall_connection_type_north", { "none", "short", "tall" } };
BlockState BlockStateRegistry::WALL_CONNECTION_TYPE_SOUTH { "wall_connection_type_south", { "none", "short", "tall" } };
BlockState BlockStateRegistry::WALL_CONNECTION_TYPE_WEST { "wall_connection_type_west", { "none", "short", "tall" } };
BlockState BlockStateRegistry::WALL_POST_BIT { "wall_post_bit", { false, true } };
BlockState BlockStateRegistry::WEEPING_VINES_AGE { "weeping_vines_age", {} };
BlockState BlockStateRegistry::WEIRDO_DIRECTION { "weirdo_direction", { 0, 1, 2, 3 } };
BlockState BlockStateRegistry::WOOD_TYPE { "wood_type",
    { "oak", "spruce", "birch", "jungle", "acacia", "dark_oak" } };