#ifndef BLOCKSTORAGE_HPP
#define BLOCKSTORAGE_HPP

#include "../../../registry/BlockRegistry.hpp"
#include "../../../util/BinaryStream.hpp"
#include "../../../nbt/NbtIo.hpp"

class BlockStorage
{
private:
    std::vector<int32_t> m_palettes;
    std::vector<uint32_t> m_blockIndexes;

public:
    BlockStorage();

    void setBlock(const Vec3& location, const Block& block);

    void serialize(BinaryStream& stream, bool isNetwork = false);

private:
    size_t fetchPalette(const Block& block);

    static int getIndex(const Vec3& location) {
        return (
            ((static_cast<int>(location.x) & 0xF) << 8)
            | ((static_cast<int>(location.z) & 0xF) << 4)
            | (static_cast<int>(location.y) & 0xF)
        );
    };

    static Vec3 getLocation(const int index) {
        return {
            static_cast<double>(index >> 8 & 0xF),
            static_cast<double>(index & 0xF),
            static_cast<double>(index >> 4 & 0xF)
        };
    };
};

#endif // !BLOCKSTORAGE_HPP
