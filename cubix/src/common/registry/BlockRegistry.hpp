#ifndef BLOCKREGISTRY_HPP
#define BLOCKREGISTRY_HPP

#include <unordered_map>

#include "../world/block/BlockDescriptor.hpp"
#include "../world/block/blocks/LogBlock.hpp"
#include "ItemRegistry.hpp"

class BlockRegistry
{
public:
    static inline Block PALE_OAK_PLANKS = { "minecraft:pale_oak_planks", -996 };
    static inline Block DARK_OAK_PLANKS = { "minecraft:dark_oak_planks", -743 };
    static inline Block ACACIA_PLANKS = { "minecraft:acacia_planks", -742 };
    static inline Block JUNGLE_PLANKS = { "minecraft:jungle_planks", -741 };
    static inline Block BIRCH_PLANKS = { "minecraft:birch_planks", -740 };
    static inline Block SPRUCE_PLANKS = { "minecraft:spruce_planks", -739 };
    static inline Block CHERRY_PLANKS = { "minecraft:cherry_planks", -537 };
    static inline Block BAMBOO_PLANKS = { "minecraft:bamboo_planks", -510 };
    static inline Block BAMBOO_MOSAIC = { "minecraft:bamboo_mosaic", -509 };
    static inline Block MANGROVE_PLANKS = { "minecraft:mangrove_planks", -486 };
    static inline Block WARPED_PLANKS = { "minecraft:warped_planks", -243 };
    static inline Block CRIMSON_PLANKS = { "minecraft:crimson_planks", -242 };

    static inline Block AIR = { "minecraft:air", -158 };

    static inline Block STONE = { "minecraft:stone", 1 };
    static inline Block GRASS_BLOCK = { "minecraft:grass_block", 2 };
    static inline Block DIRT = { "minecraft:dirt", 3 };
    static inline Block COBBLESTONE = { "minecraft:cobblestone", 4 };
    static inline Block OAK_PLANKS = { "minecraft:oak_planks", 5 };
    static inline Block OAK_LOG = LogBlock{ "minecraft:oak_log", 17 };

private:
    static inline std::vector<std::pair<std::string, Block>> s_Blocks = {};
    static inline std::unordered_map<int32_t, BlockDescriptor> s_Permutations = {};

public:
    static void initialize()
    {
        BlockRegistry::registerBlock(PALE_OAK_PLANKS);
        BlockRegistry::registerBlock(DARK_OAK_PLANKS);
        BlockRegistry::registerBlock(ACACIA_PLANKS);
        BlockRegistry::registerBlock(JUNGLE_PLANKS);
        BlockRegistry::registerBlock(BIRCH_PLANKS);
        BlockRegistry::registerBlock(SPRUCE_PLANKS);
        BlockRegistry::registerBlock(CHERRY_PLANKS);
        BlockRegistry::registerBlock(BAMBOO_PLANKS);
        BlockRegistry::registerBlock(BAMBOO_MOSAIC);
        BlockRegistry::registerBlock(MANGROVE_PLANKS);
        BlockRegistry::registerBlock(WARPED_PLANKS);
        BlockRegistry::registerBlock(CRIMSON_PLANKS);

        BlockRegistry::registerBlock(AIR, false);
        AIR.setBlockItem(ItemRegistry::AIR);

        BlockRegistry::registerBlock(STONE);
        BlockRegistry::registerBlock(GRASS_BLOCK);
        BlockRegistry::registerBlock(DIRT);
        BlockRegistry::registerBlock(COBBLESTONE);
        BlockRegistry::registerBlock(OAK_PLANKS);
        BlockRegistry::registerBlock(OAK_LOG);
    };

    static void registerBlock(Block& block, bool registerItem = true) {
        const std::string& identifier = block.getIdentifier();
        BlockRegistry::s_Blocks.emplace_back(identifier, block);
        BlockRegistry::updateNetworkIdCounter();

        if (registerItem)
        {
            Item blockItem{ identifier, block.getNetworkId() };
            ItemRegistry::registerItem(blockItem);
            block.setBlockItem(blockItem);
        };

        BlockRegistry::hashBlockStates(block);
    };

    static std::vector<BlockDescriptor> getAll() {
        std::vector<BlockDescriptor> blocks;
        blocks.reserve(s_Blocks.size());

        for (const auto &block: BlockRegistry::s_Blocks | std::views::values)
            blocks.push_back(std::make_shared<Block>(block));

        return blocks;
    };

    static const BlockDescriptor& getPermutation(const int32_t hash) {
        return BlockRegistry::s_Permutations[hash];
    };

private:
    static void updateNetworkIdCounter()
    {
        if (BlockRegistry::s_Blocks.empty())
            return;

        const auto& [ identifier, block ] = BlockRegistry::s_Blocks.back();
        blockNetIdCounter = block.getNetworkId();
    };

    static void hashBlockStates(Block& block)
    {
        // Hashes each block state
        const BlockStates& states = block.getStates();
        if (states.empty())
            return;

        std::vector<std::string> keys;
        std::vector<std::vector<StateType>> values;

        for (auto& [key, state] : states)
        {
            keys.emplace_back(key);
            values.emplace_back(state.getPossibleStates());
        };

        std::vector<size_t> indices(keys.size(), 0);
        while (true)
        {
            BlockDescriptor blockDescriptor{ std::make_shared<Block>(block) };
            for (size_t i = 0; i < keys.size(); ++i)
            {
                BlockState& newState = blockDescriptor.getState(keys[i]);
                newState.setValue(values[i][indices[i]]);
                blockDescriptor.setState(newState);
            };

            s_Permutations[blockDescriptor.hash()] = blockDescriptor;

            // Increment indices
            size_t k = keys.size();
            while (k > 0)
            {
                --k;
                if (++indices[k] < values[k].size())
                    break;

                indices[k] = 0;
                if (k == 0)
                    return; // Done
            };
        };
    };
};

#endif // !BLOCKREGISTRY_HPP