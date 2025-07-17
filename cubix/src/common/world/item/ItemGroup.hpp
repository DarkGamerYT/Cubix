#ifndef ITEMGROUP_HPP
#define ITEMGROUP_HPP
#include <string>
#include <vector>
#include <memory>

#include "ItemCategory.hpp"

static uint32_t groupIndexCounter = 0;
class Item;
class ItemGroup
{
private:
    ItemCategory m_Category = ItemCategory::Construction;
    std::string m_Name = "";
    std::shared_ptr<Item> m_Icon;
    uint32_t m_Index;
    std::vector<std::shared_ptr<Item>> m_Entries;

public:
    ItemGroup(
        ItemCategory category,
        const std::string& name = ""
    ) : m_Category(category), m_Name(name),
        m_Icon(std::make_shared<Item>(ItemGroup::defaultIcon())), m_Index(groupIndexCounter++) {};

    ItemCategory getCategory() const { return this->m_Category; };
    const std::string& getName() const { return this->m_Name; };
    const Item& getIcon() const { return *this->m_Icon; };
    uint32_t getIndex() const { return this->m_Index; };

    ItemGroup& setIcon(const Item& icon) { this->m_Icon = std::make_shared<Item>(icon); return *this; };

    ItemGroup& add(const Item& item) { this->m_Entries.emplace_back(std::make_shared<Item>(item)); return *this; };
    std::vector<std::shared_ptr<Item>> entries() const { return this->m_Entries; };

private:
    static Item& defaultIcon();
};

#endif // !ITEMGROUP_HPP
