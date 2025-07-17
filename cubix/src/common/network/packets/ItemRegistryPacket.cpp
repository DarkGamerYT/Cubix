#include "ItemRegistryPacket.hpp"
void ItemRegistryPacket::read(BinaryStream& stream)
{

};

void ItemRegistryPacket::write(BinaryStream& stream)
{
    const std::vector<Item>& items = ItemRegistry::getAll();
    stream.writeUnsignedVarInt((uint32_t)items.size());
    for (const Item& item : items)
    {
        stream.writeString(item.getIdentifier());
        stream.writeShort(item.getNetworkId());
        stream.writeBoolean(item.getParseVersion() == ItemVersion::DataDriven);
        stream.writeSignedVarInt((int)item.getParseVersion());
        Nbt::write<Endianness::NetworkEndian>(stream, item.buildNetworkTag()->copy());
    };
};