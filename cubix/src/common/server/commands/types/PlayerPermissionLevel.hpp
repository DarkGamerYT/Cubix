#ifndef PLAYERPERMISSIONLEVEL_HPP
#define PLAYERPERMISSIONLEVEL_HPP

#include <cstdint>

enum class PlayerPermissionLevel : uint8_t {
    Visitor  = 0,
    Member   = 1,
    Operator = 2,
    Custom   = 3
};

#endif //PLAYERPERMISSIONLEVEL_HPP
