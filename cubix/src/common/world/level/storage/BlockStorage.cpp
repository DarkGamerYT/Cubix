#include "BlockStorage.hpp"
BlockStorage::BlockStorage()
    : mBlockIndexes(16 * 16 * 16)
{
    mPalettes.emplace_back(BlockRegistry::AIR.getIdentifier(), Block::hash(BlockRegistry::AIR));
};

void BlockStorage::setBlock(const Vec3& location, const Block& block) {
    const auto& palette = BlockStorage::fetchPalette(block);

    const auto& index = BlockStorage::getIndex(location);
    mBlockIndexes[index] = palette;
};

size_t BlockStorage::fetchPalette(const Block& block) {
    const auto& iterator = std::ranges::find_if(mPalettes, [block](const auto& pair) {
        return pair.first == block.getIdentifier();
    });

    if (iterator != mPalettes.end())
        return std::distance(mPalettes.begin(), iterator);

    mPalettes.emplace_back(block.getIdentifier(), BlockRegistry::getBlockHash(BlockDescriptor{ block }));
    return mPalettes.size() - 1;
};

void BlockStorage::serialize(BinaryStream& stream, const bool isNetwork)
{
    int bitsPerBlock = std::ceil(std::log2(mPalettes.size()));
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

    const int blocksPerWord = std::floor(32.0 / bitsPerBlock);
    const int wordsPerBlock = std::ceil(mBlockIndexes.size() / blocksPerWord);

    for (int w = 0; w < wordsPerBlock; w++) {
        int32_t word = 0;
        for (int block = 0; block < blocksPerWord; block++)
        {
            const int index = w * blocksPerWord + block;
            if (index >= 4096)
                break;

            size_t state = 0;
            if (index < mBlockIndexes.size())
                state = mBlockIndexes[index];

            const int offset = block * bitsPerBlock;

            // Write the block state to the word
            word |= static_cast<int32_t>(state) << offset;
        };

        stream.writeInt(word);
    };

    if (isNetwork)
    {
        stream.writeSignedVarInt(static_cast<int32_t>(mPalettes.size()));
    }
    else {
        stream.writeInt(static_cast<int32_t>(mPalettes.size()));
    };
        
    for (const auto &state: mPalettes | std::views::values)
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