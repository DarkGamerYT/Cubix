#ifndef BLOCKSTORAGE_HPP
#define BLOCKSTORAGE_HPP

#include "../../../registry/BlockRegistry.hpp"
#include "../../../util/BinaryStream.hpp"
#include "../../../nbt/NbtIo.hpp"

class BlockStorage
{
public:
    BlockStorage();

    void serialize(BinaryStream& stream, bool isNetwork = false);
};

#endif // !BLOCKSTORAGE_HPP
