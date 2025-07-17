#include "BlockStorage.hpp"
BlockStorage::BlockStorage()
{

};

void BlockStorage::serialize(BinaryStream& stream, bool isNetwork)
{
    std::vector<int32_t> palettes = {};
    palettes.push_back(Block::hash(BlockRegistry::STONE));
    palettes.push_back(Block::hash(BlockRegistry::COBBLESTONE));
    palettes.push_back(Block::hash(BlockRegistry::DIRT));

    int bitsPerBlock = std::ceil(std::log2(palettes.size()));
    switch (bitsPerBlock)
    {
        case 0:
            bitsPerBlock = 1; break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            break;
        case 7:
        case 8:
            bitsPerBlock = 8; break;
        default:
            bitsPerBlock = 16; break;
    };

    stream.writeByte((bitsPerBlock << 1) | 1);

    int blocksPerWord = std::floor(32.0 / bitsPerBlock);
    int wordsPerBlock = std::ceil(4096.0 / blocksPerWord);

    for (int w = 0; w < wordsPerBlock; w++) {
        int32_t word = 0;
        for (int block = 0; block < blocksPerWord; block++)
        {
            int index = w * blocksPerWord + block;
            if (index >= 4096)
                break;

            int state = 0;
            if (index < palettes.size())
                state = palettes[index];

            int offset = block * bitsPerBlock;

            // Write the block state to the word
            word |= state << offset;
        };

        stream.writeInt(word);
    };

    if (isNetwork)
    {
        stream.writeSignedVarInt(static_cast<int32_t>(palettes.size()));
    }
    else {
        stream.writeInt(palettes.size());
    };
        
    for (int32_t state : palettes)
    {
        if (isNetwork)
        {
            stream.writeSignedVarInt(state);
            continue;
        };

        // Nbt stuff
        const BlockDescriptor& block = BlockRegistry::getPermutation(state);
        Nbt::write(stream, block.serialise()->copy());
    };
};