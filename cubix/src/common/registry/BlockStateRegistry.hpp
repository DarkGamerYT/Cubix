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
    static BlockState ACTIVE;
    static BlockState AGE;
    static BlockState AGE_BIT;
    static BlockState ALLOW_UNDERWATER_BIT;
    static BlockState ATTACHED_BIT;
    static BlockState ATTACHMENT;
    static BlockState BAMBOO_LEAF_SIZE;
    static BlockState BAMBOO_STALK_THICKNESS;
    static BlockState BIG_DRIPLEAF_HEAD;
    static BlockState BIG_DRIPLEAF_TILT;
    static BlockState BITE_COUNTER;
    static BlockState BLOCK_LIGHT_LEVEL;
    static BlockState BLOOM;
    static BlockState BOOKS_STORED;
    static BlockState BREWINGSTAND_SLOT_A;
    static BlockState BREWINGSTAND_SLOT_B;
    static BlockState BREWINGSTAND_SLOT_C;
    static BlockState BRUSHED_PROGRESS;
    static BlockState BUTTON_PRESSED_BIT;
    static BlockState CAN_SUMMON;
    static BlockState CANDLES;

    static BlockState PERSISTENT_BIT;
    static BlockState PILLAR_AXIS;
    static BlockState PORTAL_AXIS;
    static BlockState POWERED_BIT;
    static BlockState PRISMARINE_BLOCK_TYPE;
    static BlockState PROPAGULE_STAGE;
    static BlockState RAIL_DATA_BIT;
    static BlockState RAIL_DIRECTION;
    static BlockState REDSTONE_SIGNAL;
    static BlockState REPEATER_DELAY;
    static BlockState RESPAWN_ANCHOR_CHARGE;
    static BlockState ROTATION;

    static BlockState STRIPPED_BIT;
    static BlockState STRUCTURE_BLOCK_TYPE;
    static BlockState STRUCTURE_VOID_TYPE;
    static BlockState SUSPENDED_BIT;
    static BlockState TALL_GRASS_TYPE;
    static BlockState TIP;
    static BlockState TOGGLE_BIT;
    static BlockState TOP_SLOT_BIT;
    static BlockState TORCH_FACING_DIRECTION;
    static BlockState TRIAL_SPAWNER_STATE;
    static BlockState TRIGGERED_BIT;
    static BlockState TURTLE_EGG_COUNT;
    static BlockState TWISTING_VINES_AGE;
    static BlockState UPDATE_BIT;
    static BlockState UPPER_BLOCK_BIT;
    static BlockState UPSIDE_DOWN_BIT;
    static BlockState VAULT_STATE;
    static BlockState VINE_DIRECTION;
    static BlockState WALL_BLOCK_TYPE;
    static BlockState WALL_CONNECTION_TYPE_EAST;
    static BlockState WALL_CONNECTION_TYPE_NORTH;
    static BlockState WALL_CONNECTION_TYPE_SOUTH;
    static BlockState WALL_CONNECTION_TYPE_WEST;
    static BlockState WALL_POST_BIT;
    static BlockState WEEPING_VINES_AGE;
    static BlockState WEIRDO_DIRECTION;
    static BlockState WOOD_TYPE;
};

#endif // !BLOCKSTATEREGISTRY_HPP