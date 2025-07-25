#ifndef COMMANDPERMISSIONLEVEL_HPP
#define COMMANDPERMISSIONLEVEL_HPP

#include <cstdint>

enum class CommandPermissionLevel : uint8_t {
    Any           = 0,
    GameDirectors = 1,
    Admin         = 2,
    Host          = 3,
    Owner         = 4,
    Internal      = 5
};

#endif // !COMMANDPERMISSIONLEVEL_HPP