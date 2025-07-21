#include "BlockStorage.hpp"
BlockStorage::BlockStorage()
    : m_blockIndexes(16 * 16 * 16)
{
    m_palettes.push_back(Block::hash(BlockRegistry::AIR));
};

void BlockStorage::setBlock(const Vec3& location, const Block& block) {
    const auto& palette = BlockStorage::fetchPalette(block);

    const auto& index = BlockStorage::getIndex(location);
    m_blockIndexes[index] = palette;
};

size_t BlockStorage::fetchPalette(const Block& block) {
    const auto& hash = Block::hash(block);

    const auto& iterator = std::ranges::find(m_palettes, hash);
    if (iterator != m_palettes.end())
        return std::distance(m_palettes.begin(), iterator);

    m_palettes.push_back(hash);
    return m_palettes.size() - 1;
};

void BlockStorage::serialize(BinaryStream& stream, const bool isNetwork)
{
    int bitsPerBlock = std::ceil(std::log2(m_palettes.size()));
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
    const int wordsPerBlock = std::ceil(m_blockIndexes.size() / blocksPerWord);

    for (int w = 0; w < wordsPerBlock; w++) {
        int32_t word = 0;
        for (int block = 0; block < blocksPerWord; block++)
        {
            const int index = w * blocksPerWord + block;
            if (index >= 4096)
                break;

            int state = 0;
            if (index < m_blockIndexes.size())
                state = m_blockIndexes[index];

            const int offset = block * bitsPerBlock;

            // Write the block state to the word
            word |= state << offset;
        };

        stream.writeInt(word);
    };

    if (isNetwork)
    {
        stream.writeSignedVarInt(static_cast<int32_t>(m_palettes.size()));
    }
    else {
        stream.writeInt(m_palettes.size());
    };
        
    for (const int32_t state : m_palettes)
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