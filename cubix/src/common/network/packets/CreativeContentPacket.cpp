#include "CreativeContentPacket.hpp"
void CreativeContentPacket::read(BinaryStream& stream)
{

};

void CreativeContentPacket::write(BinaryStream& stream)
{
    // Creative Groups
    const std::vector<ItemGroup>& groups = ItemGroupRegistry::getAll();
    size_t groupsCount = groups.size();

    // Items
    std::vector<Item> items;

    stream.writeUnsignedVarInt((uint32_t)groupsCount);
    for (const ItemGroup& group : groups)
    {
        stream.writeInt((int)group.getCategory());
        stream.writeString<Endianness::NetworkEndian>(group.getName());

        Item icon = group.getIcon();
        if (icon == ItemRegistry::INVALID)
        {
            stream.writeByte(0);
        }
        else {
            stream.writeItem(icon);
        };

        for (auto& item : group.entries())
        {
            item->setCreativeGroup(group);
            items.emplace_back(*item);
        };
    };

    stream.writeUnsignedVarInt((uint32_t)items.size());
    for (Item& item : items)
    {
        stream.writeUnsignedVarInt(item.getNetworkId()); // Creative item index
        stream.writeItem(item);
        stream.writeUnsignedVarInt(item.getCreativeGroup().getIndex());
    };
};