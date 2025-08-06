#include "BlockDescriptor.hpp"
#include "../../nbt/NbtIo.hpp"
std::unique_ptr<Nbt::CompoundTag> BlockDescriptor::serialise() const
{
    return this->mBlock->serialise();
};

int32_t BlockDescriptor::hash() const
{
    return Block::hash(*this->mBlock);
};