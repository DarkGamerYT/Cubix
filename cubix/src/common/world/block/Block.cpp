#include "Block.hpp"
#include "../../util/BinaryStream.hpp"
#include "../../nbt/NbtIo.hpp"

#include "../../registry/ItemRegistry.hpp"

Block& Block::setBlockItem(Item& item)
{
    this->m_BlockItem = std::make_shared<Item>(item);
    return *this;
};

std::unique_ptr<Nbt::CompoundTag> Block::serialise() const
{
    Nbt::CompoundTag root;
    root.add("name", Nbt::StringTag(this->m_Identifier));

    Nbt::CompoundTag states;
    for (const auto& [key, state] : this->m_States)
    {
        if (const int type = state.type(); type == 0)
        {
            Nbt::StringTag tag{ std::get<std::string>(state.getValue()) };
            states.add(key, tag);
        }
        else if (type == 1)
        {
            Nbt::IntTag tag{ std::get<int>(state.getValue()) };
            states.add(key, tag);
        }
        else {
            Nbt::ByteTag tag{ std::get<bool>(state.getValue()) };
            states.add(key, tag);
        };
    };
    root.add("states", states);
    root.add("version", Nbt::IntTag(SharedConstants::CurrentGameVersion.encode()));
    return std::make_unique<Nbt::CompoundTag>(root);
};

int32_t Block::hash(const Block& block)
{
    const std::unique_ptr<Nbt::CompoundTag> root = block.serialise();
    root->erase("version");

    // Hashing stuff
    BinaryStream stream;
    Nbt::write(stream, root->copy());

    const std::vector<uint8_t>& data = stream.mStream;
    int32_t hash = 0x811C9DC5;
    for (const uint8_t byte : data)
    {
        hash ^= byte & 0xff;
        hash += (hash << 1) + (hash << 4) + (hash << 7) + (hash << 8) + (hash << 24);
    };

    return hash;
};