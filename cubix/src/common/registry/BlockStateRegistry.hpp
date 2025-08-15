#ifndef BLOCKSTATEREGISTRY_HPP
#define BLOCKSTATEREGISTRY_HPP

#include "../world/block/BlockState.hpp"

class BlockStateRegistry
{
private:
    static inline std::vector<BlockState> sStates{};

public:
    static void initialize();

    static const std::vector<BlockState>& getAll() { return sStates; };

public:
    static inline BlockState ACTIVE = { "active", { false, true } };
    static inline BlockState AGE = { "age", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } };
    static inline BlockState AGE_BIT = { "age_bit", { false, true } };
    static inline BlockState ALLOW_UNDERWATER_BIT = { "allow_underwater_bit", { false, true } };
    static inline BlockState ATTACHED_BIT = { "attached_bit", { false, true } };
    static inline BlockState ATTACHMENT = { "attachment", { "standing", "hanging", "side", "multiple" } };
    static inline BlockState BAMBOO_LEAF_SIZE = { "bamboo_leaf_size", { "no_leaves", "small_leaves", "large_leaves" } };
    static inline BlockState BAMBOO_STALK_THICKNESS = { "bamboo_stalk_thickness", { "thin", "thick" } };
    static inline BlockState BIG_DRIPLEAF_HEAD = { "big_dripleaf_head", { false, true } };
    static inline BlockState BIG_DRIPLEAF_TILT = { "big_dripleaf_tilt", { "none", "unstable", "partial_tilt", "full_tilt" } };
    static inline BlockState BITE_COUNTER = { "bite_counter", { 0, 1, 2, 3, 4, 5, 6 } };
    static inline BlockState BLOCK_LIGHT_LEVEL = { "block_light_level",
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } };
    static inline BlockState BLOOM = { "bloom", { false, true } };
    static inline BlockState BOOKS_STORED = { "books_stored", {} };
    static inline BlockState BREWINGSTAND_SLOT_A = { "brewing_stand_slot_a_bit", { false, true } };
    static inline BlockState BREWINGSTAND_SLOT_B = { "brewing_stand_slot_b_bit", { false, true } };
    static inline BlockState BREWINGSTAND_SLOT_C = { "brewing_stand_slot_c_bit", { false, true } };
    static inline BlockState BRUSHED_PROGRESS = { "brushed_progress", { 0, 1, 2, 3 } };
    static inline BlockState BUTTON_PRESSED_BIT = { "button_pressed_bit", { false, true } };
    static inline BlockState CAN_SUMMON = { "can_summon", { false, true } };
    static inline BlockState CANDLES = { "candles", { 0, 1, 2, 3 } };

    static inline BlockState PERSISTENT_BIT = { "persistent_bit", { false, true } };
    static inline BlockState PILLAR_AXIS = { "pillar_axis", { "x", "y", "z" } };
    static inline BlockState PORTAL_AXIS = { "portal_axis", { "unknown", "x", "z" } };
    static inline BlockState POWERED_BIT = { "powered_bit", { false, true } };
    static inline BlockState PRISMARINE_BLOCK_TYPE = { "prismarine_block_type", { "default", "dark", "bricks" } };
    static inline BlockState PROPAGULE_STAGE = { "propagule_stage", { 0, 1, 2, 3, 4 } };
    static inline BlockState RAIL_DATA_BIT = { "rail_data_bit", { false, true } };
    static inline BlockState RAIL_DIRECTION = { "rail_direction", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } };
    static inline BlockState REDSTONE_SIGNAL = { "redstone_signal",
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } };
    static inline BlockState REPEATER_DELAY = { "repeater_delay", { 0, 1, 2, 3 } };
    static inline BlockState RESPAWN_ANCHOR_CHARGE = { "respawn_anchor_charge", { 0, 1, 2, 3, 4 } };
    static inline BlockState ROTATION = { "rotation", { 0, 1, 2, 3 } };

    static inline BlockState STRIPPED_BIT = { "stripped_bit", { false, true } };
    static inline BlockState STRUCTURE_BLOCK_TYPE = { "structure_block_type",
        { "data", "save", "load", "corner", "invalid", "export" } };
    static inline BlockState STRUCTURE_VOID_TYPE = { "structure_void_type", { "void", "air" } };
    static inline BlockState SUSPENDED_BIT = { "suspended_bit", { false, true } };
    static inline BlockState TALL_GRASS_TYPE = { "tall_grass_type", { "default", "tall", "fern", "snow" } };
    static inline BlockState TIP = { "tip", { false, true } };
    static inline BlockState TOGGLE_BIT = { "toggle_bit", { false, true } };
    static inline BlockState TOP_SLOT_BIT = { "top_slot_bit", { false, true } };
    static inline BlockState TORCH_FACING_DIRECTION = { "torch_facing_direction",
        { "unknown", "west", "east", "north", "south", "top" } };
    static inline BlockState TRIAL_SPAWNER_STATE = { "trial_spawner_state", { 0, 1, 2, 3, 4, 5 } };
    static inline BlockState TRIGGERED_BIT = { "triggered_bit", { false, true } };
    static inline BlockState TURTLE_EGG_COUNT = { "turtle_egg_count", { "one_egg", "two_egg", "three_egg", "four_egg" } };
    static inline BlockState TWISTING_VINES_AGE = { "twisting_vines_age", {} };
    static inline BlockState UPDATE_BIT = { "update_bit", { false, true } };
    static inline BlockState UPPER_BLOCK_BIT = { "upper_block_bit", { false, true } };
    static inline BlockState UPSIDE_DOWN_BIT = { "upside_down_bit", { false, true } };
    static inline BlockState VAULT_STATE = { "vault_state", { "inactive", "active", "unlocking", "ejecting" } };
    static inline BlockState VINE_DIRECTION = { "vine_direction_bits",
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 } };
    static inline BlockState WALL_BLOCK_TYPE = { "wall_block_type", {
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
    static inline BlockState WALL_CONNECTION_TYPE_EAST = { "wall_connection_type_east", { "none", "short", "tall" } };
    static inline BlockState WALL_CONNECTION_TYPE_NORTH = { "wall_connection_type_north", { "none", "short", "tall" } };
    static inline BlockState WALL_CONNECTION_TYPE_SOUTH = { "wall_connection_type_south", { "none", "short", "tall" } };
    static inline BlockState WALL_CONNECTION_TYPE_WEST = { "wall_connection_type_west", { "none", "short", "tall" } };
    static inline BlockState WALL_POST_BIT = { "wall_post_bit", { false, true } };
    static inline BlockState WEEPING_VINES_AGE = { "weeping_vines_age", {} };
    static inline BlockState WEIRDO_DIRECTION = { "weirdo_direction", { 0, 1, 2, 3 } };
    static inline BlockState WOOD_TYPE = { "wood_type",
        { "oak", "spruce", "birch", "jungle", "acacia", "dark_oak" } };
};

#endif // !BLOCKSTATEREGISTRY_HPP