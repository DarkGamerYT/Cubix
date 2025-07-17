#include "BlockDescriptor.hpp"
#include "../../nbt/NbtIo.hpp"
std::unique_ptr<Nbt::CompoundTag> BlockDescriptor::serialise() const
{
    std::unique_ptr<Nbt::CompoundTag> root = this->m_Block->serialise();
    return root;
};

int32_t BlockDescriptor::hash() const
{
    return -1;
};