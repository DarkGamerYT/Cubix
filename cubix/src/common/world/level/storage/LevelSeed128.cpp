#include "LevelSeed128.hpp"
LevelSeed128::LevelSeed128(const uint64_t seed) {
    constexpr uint64_t XOR_CONSTANT = 0x6A09E667F3BCC909ULL;
    constexpr uint64_t SUB_CONSTANT = 0x61C8864680B583EBULL;

    const uint64_t value = (seed ^ XOR_CONSTANT);

    uint64_t low  = LevelSeed128::mix(value);
    uint64_t high = LevelSeed128::mix(value - SUB_CONSTANT);

    // Fallback if both values are zero
    if (low == 0 && high == 0)
    {
        low = 0x9E3779B97F4A7C15ULL;
        high = 0x6A09E667F3BCC909ULL;
    };

    this->low = low;
    this->high = high;
};

uint64_t LevelSeed128::mix(uint64_t input) {
    constexpr uint64_t MIX1 = 0xBF58476D1CE4E5B9ULL;
    constexpr uint64_t MIX2 = 0x94D049BB133111EBULL;

    input ^= (input >> 30);
    input *= MIX1;
    input ^= (input >> 27);
    input *= MIX2;
    return input ^ (input >> 31);
};