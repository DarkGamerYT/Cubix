#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdint>
#include <memory>
#include <limits>

#include "IRandom.hpp"
#include "MarsagliaPolarGaussian.hpp"

#include "../../world/level/storage/LevelSeed64.hpp"

class Random final : public IRandom {
private:
    static constexpr int STATE_SIZE = 624;
    uint32_t _mt[STATE_SIZE] = {};
    int _mti = STATE_SIZE;
    int mInitedIdx = 398;

    uint32_t mSeed = 0;
    MarsagliaPolarGaussian mGaussianSource;

public:
    Random();
    explicit Random(uint32_t seed);

    int nextInt(int bound) override;
    int nextInt() override;
    int64_t nextLong() override;
    float nextFloat() override;
    double nextDouble() override;
    bool nextBoolean() override;
    double nextGaussianDouble() override;

    void consumeCount(uint32_t count) override;
    std::unique_ptr<IRandom> fork() override;

private:
    void _setSeed(uint32_t seed);
    uint32_t _genRandInt32(); // core MT implementation
};

#endif //RANDOM_HPP
