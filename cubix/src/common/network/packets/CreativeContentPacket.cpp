#include "CreativeContentPacket.hpp"
void CreativeContentPacket::read(BinaryStream& stream)
{

};

void CreativeContentPacket::write(BinaryStream& stream)
{
    // Creative Groups
    const std::vector<ItemGroup>& groups = ItemGroupRegistry::getAll();
    const size_t groupsCount = groups.size();

    // Items
    std::vector<std::shared_ptr<Item>> items;

    stream.writeUnsignedVarInt(static_cast<uint32_t>(groupsCount));
    for (const ItemGroup& group : groups)
    {
        stream.writeInt(static_cast<int>(group.getCategory()));
        stream.writeString<Endianness::NetworkEndian>(group.getName());

        const Item icon = group.getIcon();
        if (icon == ItemRegistry::INVALID)
            stream.writeByte(0);
        else {
            stream.writeItem(std::make_shared<Item>(icon));
        };

        for (auto& item : group.entries())
        {
            item->setCreativeGroup(group);
            items.emplace_back(item);
        };
    };

    stream.writeUnsignedVarInt(static_cast<uint32_t>(items.size()));
    for (auto& itemStack : items)
    {
        stream.writeUnsignedVarInt(itemStack->getNetworkId()); // Creative item index
        stream.writeItem(itemStack);
        stream.writeUnsignedVarInt(itemStack->getCreativeGroup().getIndex());
    };
};