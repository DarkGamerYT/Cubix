#ifndef LEVELSEED128_HPP
#define LEVELSEED128_HPP

#include <cstdint>

#include "LevelSeed64.hpp"

class LevelSeed128 {
public:
    uint64_t low = 0;
    uint64_t high = 0;

public:
    LevelSeed128()
        : LevelSeed128(LevelSeed64{}.getSeed()) {};

    explicit LevelSeed128(uint64_t);
    explicit LevelSeed128(const uint64_t low, const uint64_t high)
        : low(low), high(high) {};

    bool isZero() const { return (low | high) == 0; };

private:
    static uint64_t mix(uint64_t input);
};

#endif //LEVELSEED128_HPP
