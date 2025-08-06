#ifndef BLOCKDESCRIPTOR_HPP
#define BLOCKDESCRIPTOR_HPP

#include "Block.hpp"

class BlockDescriptor
{
private:
    std::shared_ptr<Block> mBlock;
    BlockStates mStates;

public:
    BlockDescriptor() = default;
    explicit BlockDescriptor(const Block& block)
        : mBlock(std::make_shared<Block>(block)), mStates(mBlock->getStates()) {};

    explicit BlockDescriptor(const std::shared_ptr<Block>& block)
        : mBlock(block), mStates(mBlock->getStates()) {};

    const std::string& getIdentifier() const { return this->mBlock->getIdentifier(); };
    int32_t getNetworkId() const { return this->mBlock->getNetworkId(); };

    BlockState& getState(const std::string& key) { return this->mStates[key]; };
    BlockStates getStates() const { return this->mStates; };

    void setState(BlockState& state) { this->mStates.emplace(state.identifier(), state); };

    const std::shared_ptr<Block>& getBlock() const { return this->mBlock; };
    bool isValid() const { return this->mBlock != nullptr; };

    int32_t hash() const;
    std::unique_ptr<Nbt::CompoundTag> serialise() const;
};

#endif // !BLOCKDESCRIPTOR_HPP
