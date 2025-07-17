#ifndef SUBCLIENTID_HPP
#define SUBCLIENTID_HPP

#include <cstdint>

enum class SubClientId : uint8_t {
    PrimaryClient = 0,
    Client2       = 1,
    Client3       = 2,
    Client4       = 3
};

#endif //SUBCLIENTID_HPP