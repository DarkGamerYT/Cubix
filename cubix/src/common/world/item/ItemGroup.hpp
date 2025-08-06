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
    ItemCategory mCategory = ItemCategory::Construction;
    std::string mName = "";
    std::shared_ptr<Item> mIcon;
    uint32_t mIndex;
    std::vector<std::shared_ptr<Item>> mEntries;

public:
    explicit ItemGroup(
        const ItemCategory category,
        const std::string& name = ""
    ) : mCategory(category), mName(name),
        mIcon(std::make_shared<Item>(ItemGroup::defaultIcon())), mIndex(groupIndexCounter++) {};

    ItemCategory getCategory() const { return this->mCategory; };
    const std::string& getName() const { return this->mName; };
    const Item& getIcon() const { return *this->mIcon; };
    uint32_t getIndex() const { return this->mIndex; };

    ItemGroup& setIcon(const Item& icon) { this->mIcon = std::make_shared<Item>(icon); return *this; };

    ItemGroup& add(const Item& item) { this->mEntries.emplace_back(std::make_shared<Item>(item)); return *this; };
    std::vector<std::shared_ptr<Item>> entries() const { return this->mEntries; };

private:
    static Item& defaultIcon();
};

#endif // !ITEMGROUP_HPP
