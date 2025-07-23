#include "BlockRegistry.hpp"
void BlockRegistry::initialize()
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

void BlockRegistry::registerBlock(Block& block, const bool registerItem) {
    const std::string& identifier = block.getIdentifier();
    BlockRegistry::sBlocks.emplace_back(identifier, block);
    BlockRegistry::updateNetworkIdCounter();

    if (registerItem)
    {
        Item blockItem{ identifier, block.getNetworkId() };
        ItemRegistry::registerItem(blockItem);
        block.setBlockItem(blockItem);
    };

    BlockRegistry::hashBlockStates(block);
};

std::vector<BlockDescriptor> BlockRegistry::getAll() {
    std::vector<BlockDescriptor> blocks;
    blocks.reserve(sBlocks.size());

    for (const auto &block: BlockRegistry::sBlocks | std::views::values)
        blocks.push_back(std::make_shared<Block>(block));

    return blocks;
};

const BlockDescriptor& BlockRegistry::getPermutation(const int32_t hash) {
    return BlockRegistry::sPermutations[hash];
};

void BlockRegistry::updateNetworkIdCounter()
{
    if (BlockRegistry::sBlocks.empty())
        return;

    const auto& [ identifier, block ] = BlockRegistry::sBlocks.back();
    blockNetIdCounter = block.getNetworkId();
};

void BlockRegistry::hashBlockStates(Block& block)
{
    // Hashes each Block BlockRegistry::state
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

        sPermutations[blockDescriptor.hash()] = blockDescriptor;

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

// Blocks
Block BlockRegistry::PALE_OAK_PLANKS = { "minecraft:pale_oak_planks", -996 };
Block BlockRegistry::DARK_OAK_PLANKS = { "minecraft:dark_oak_planks", -743 };
Block BlockRegistry::ACACIA_PLANKS = { "minecraft:acacia_planks", -742 };
Block BlockRegistry::JUNGLE_PLANKS = { "minecraft:jungle_planks", -741 };
Block BlockRegistry::BIRCH_PLANKS = { "minecraft:birch_planks", -740 };
Block BlockRegistry::SPRUCE_PLANKS = { "minecraft:spruce_planks", -739 };
Block BlockRegistry::CHERRY_PLANKS = { "minecraft:cherry_planks", -537 };
Block BlockRegistry::BAMBOO_PLANKS = { "minecraft:bamboo_planks", -510 };
Block BlockRegistry::BAMBOO_MOSAIC = { "minecraft:bamboo_mosaic", -509 };
Block BlockRegistry::MANGROVE_PLANKS = { "minecraft:mangrove_planks", -486 };
Block BlockRegistry::WARPED_PLANKS = { "minecraft:warped_planks", -243 };
Block BlockRegistry::CRIMSON_PLANKS = { "minecraft:crimson_planks", -242 };

Block BlockRegistry::AIR = { "minecraft:air", -158 };

Block BlockRegistry::STONE = { "minecraft:stone", 1 };
Block BlockRegistry::GRASS_BLOCK = { "minecraft:grass_block", 2 };
Block BlockRegistry::DIRT = { "minecraft:dirt", 3 };
Block BlockRegistry::COBBLESTONE = { "minecraft:cobblestone", 4 };
Block BlockRegistry::OAK_PLANKS = { "minecraft:oak_planks", 5 };
Block BlockRegistry::OAK_LOG = LogBlock{ "minecraft:oak_log", 17 };