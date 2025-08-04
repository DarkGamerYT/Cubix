#ifndef LEVELSEED64_HPP
#define LEVELSEED64_HPP

#include <cstdint>
#include <string>
#include <random>

#include "../../../util/StringUtils.hpp"

class LevelSeed64 {
private:
    uint64_t mSeed;

public:
    LevelSeed64();
    explicit LevelSeed64(std::string input);
    explicit LevelSeed64(const uint64_t seed)
        : mSeed(seed) {};

    uint64_t getSeed() const { return this->mSeed; };
    std::string toString() const {
        return std::to_string(static_cast<int64_t>(this->mSeed));
    };

private:
    static uint64_t generate();
};

#endif //LEVELSEED64_HPP
