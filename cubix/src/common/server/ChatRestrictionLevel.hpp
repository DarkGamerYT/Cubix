#ifndef CHATRESTRICTIONLEVEL_HPP
#define CHATRESTRICTIONLEVEL_HPP

#include <cstdint>

enum class ChatRestrictionLevel : uint8_t {
    None     = 0,
    Dropped  = 1,
    Disabled = 2,
};

#endif //CHATRESTRICTIONLEVEL_HPP
