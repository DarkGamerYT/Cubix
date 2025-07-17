#ifndef BLOCKDESCRIPTOR_HPP
#define BLOCKDESCRIPTOR_HPP

#include "Block.hpp"

class BlockDescriptor
{
private:
    std::shared_ptr<Block> m_Block;
    BlockStates m_States;

public:
    BlockDescriptor() {};
    BlockDescriptor(const std::shared_ptr<Block>& block)
        : m_Block(std::move(block)), m_States(m_Block->getStates()) {};

    const std::string& getIdentifier() const { return this->m_Block->getIdentifier(); };
    int32_t getNetworkId() const { return this->m_Block->getNetworkId(); };

    BlockState& getState(const std::string& key) { return this->m_States[key]; };
    BlockStates getStates() const { return this->m_States; };

    void setState(BlockState& state) { this->m_States.emplace(state.identifier(), state); };

    const std::shared_ptr<Block>& getBlock() const { return this->m_Block; };
    bool isValid() const { return this->m_Block != nullptr; };

    int32_t hash() const;
    std::unique_ptr<Nbt::CompoundTag> serialise() const;
};

#endif // !BLOCKDESCRIPTOR_HPP
