#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <unordered_map>
#include <vector>
#include <sstream>

#include "../../SharedConstants.hpp"
#include "../../molang/MolangVersion.hpp"

#include "BlockState.hpp"

namespace Nbt { class CompoundTag; };

static int32_t blockNetIdCounter = 1;
typedef std::unordered_map<std::string, BlockState> BlockStates;
class Item;
class Block
{
private:
    std::string mIdentifier;
    int32_t mNetId = 0; // Invalid block
    BlockStates mStates;
    std::shared_ptr<Item> mBlockItem;

public:
    Block() : mIdentifier("minecraft:invalid") {};
    Block(const std::string& identifier, const int id)
        : mIdentifier(identifier), mNetId(id) {};
    explicit Block(const std::string& identifier)
        : mIdentifier(identifier), mNetId(blockNetIdCounter++) {};

    const std::string& getIdentifier() const { return this->mIdentifier; };
    int32_t getNetworkId() const { return this->mNetId; };
    const Item& getBlockItem() const { return *this->mBlockItem; };

    BlockState& getState(const std::string& key) { return this->mStates[key]; };
    BlockStates getStates() const { return this->mStates; };


    Block& setBlockItem(Item& item);

    void setState(const BlockState& state) { this->mStates.emplace(state.identifier(), state); };


    static int32_t hash(const Block&);
    std::unique_ptr<Nbt::CompoundTag> serialise() const;
};

#endif // !BLOCK_HPP
