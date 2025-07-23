#ifndef BLOCKREGISTRY_HPP
#define BLOCKREGISTRY_HPP

#include <ranges>
#include <unordered_map>

#include "../world/block/BlockDescriptor.hpp"
#include "../world/block/blocks/LogBlock.hpp"
#include "ItemRegistry.hpp"

class BlockRegistry
{
public:
    static Block PALE_OAK_PLANKS;
    static Block DARK_OAK_PLANKS;
    static Block ACACIA_PLANKS;
    static Block JUNGLE_PLANKS;
    static Block BIRCH_PLANKS;
    static Block SPRUCE_PLANKS;
    static Block CHERRY_PLANKS;
    static Block BAMBOO_PLANKS;
    static Block BAMBOO_MOSAIC;
    static Block MANGROVE_PLANKS;
    static Block WARPED_PLANKS;
    static Block CRIMSON_PLANKS;

    static Block AIR;

    static Block STONE;
    static Block GRASS_BLOCK;
    static Block DIRT;
    static Block COBBLESTONE;
    static Block OAK_PLANKS;
    static Block OAK_LOG;

private:
    static inline std::vector<std::pair<std::string, Block>> sBlocks{};
    static inline std::unordered_map<int32_t, BlockDescriptor> sPermutations{};

public:
    static void initialize();

    static void registerBlock(Block& block, bool registerItem = true);

    static std::vector<BlockDescriptor> getAll();
    static const BlockDescriptor& getPermutation(const int32_t hash);

private:
    static void updateNetworkIdCounter();
    static void hashBlockStates(Block& block);
};

#endif // !BLOCKREGISTRY_HPP