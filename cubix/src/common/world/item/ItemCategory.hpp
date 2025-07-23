#ifndef ITEMCATEGORY_HPP
#define ITEMCATEGORY_HPP

enum class ItemCategory : int {
    All             = 0,
    Construction    = 1,
    Nature          = 2,
    Equipment       = 3,
    Items           = 4,
    ItemCommandOnly = 5,
    Undefined       = 6
};

#endif // !ITEMCATEGORY_HPP