#include "LevelSeed64.hpp"

#include "../../../util/Logger.hpp"

LevelSeed64::LevelSeed64() {
    this->mSeed = LevelSeed64::generate();
};

LevelSeed64::LevelSeed64(std::string input) {
    Util::stringTrim(input, "\t\n\v\f\r ");
    if (input.empty())
    {
        this->mSeed = LevelSeed64::generate();
        return;
    };

    if (!Util::isInteger(input))
    {
        this->mSeed = static_cast<uint64_t>(Util::hashCode(input));
        return;
    };

    this->mSeed = std::stoull(input);
};

uint64_t LevelSeed64::generate() {
    std::random_device random;
    const uint64_t high = static_cast<uint64_t>(random()) << 32;
    const uint64_t low = random();

    return high | low;
};