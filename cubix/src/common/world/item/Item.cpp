#include "Item.hpp"
#include "../../registry/ItemGroupRegistry.hpp"
std::unique_ptr<Nbt::CompoundTag> Item::buildNetworkTag() const
{
    Nbt::CompoundTag data;

    //Nbt::CompoundTag properties;
    //data.add("item_properties", properties);

    return std::make_unique<Nbt::CompoundTag>(data);
};

ItemGroup& Item::defaultCreativeGroup(Item& item)
{
    if (item.m_BlockId != 0)
    {
        return ItemGroupRegistry::PLANKS;
    }
    else {
        return ItemGroupRegistry::PLANKS;
    };
};