#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <unordered_map>
#include <vector>
#include <sstream>

#include "../../SharedConstants.hpp"
#include "../../molang/MolangVersion.hpp"

#include "BlockState.hpp"

namespace Nbt { class CompoundTag; };

static uint32_t blockNetIdCounter = 1;
typedef std::unordered_map<std::string, BlockState> BlockStates;
class Item;
class Block
{
private:
    std::string m_Identifier;
    int32_t m_NetId = 0; // Invalid block
    BlockStates m_States;
    std::shared_ptr<Item> m_BlockItem;

public:
    Block() : m_Identifier("minecraft:invalid") {};
    Block(const std::string& identifier) : m_Identifier(identifier), m_NetId(blockNetIdCounter++) {};
    Block(const std::string& identifier, int id) : m_Identifier(identifier), m_NetId(id) {};

    const std::string& getIdentifier() const { return this->m_Identifier; };
    int32_t getNetworkId() const { return this->m_NetId; };
    const Item& getBlockItem() const { return *this->m_BlockItem; };

    BlockState& getState(const std::string& key) { return this->m_States[key]; };
    BlockStates getStates() const { return this->m_States; };


    Block& setBlockItem(Item& item);

    void setState(BlockState& state) { this->m_States.emplace(state.identifier(), state); };


    static int32_t hash(const Block&);
    std::unique_ptr<Nbt::CompoundTag> serialise() const;
};

#endif // !BLOCK_HPP
