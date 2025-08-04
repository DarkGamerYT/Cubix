#ifndef SIMPLERANDOM_HPP
#define SIMPLERANDOM_HPP

#include "IRandom.hpp"
#include "IPositionalRandom.hpp"
#include "MarsagliaPolarGaussian.hpp"

#include "../../world/level/storage/LevelSeed64.hpp"

class SimpleRandom final : public IRandom, IPositionalRandom {
private:
    static constexpr uint64_t MULTIPLIER = 0x5DEECE66DULL;
    static constexpr uint64_t ADDEND = 0xBULL;
    static constexpr uint64_t MASK = (1ULL << 48) - 1;

    uint64_t mSeed = 0;
    MarsagliaPolarGaussian mGaussianSource;

public:
    SimpleRandom();
    explicit SimpleRandom(const LevelSeed64& seed);

    void setSeed(const LevelSeed64& seed);

    int nextInt() override;
    int nextInt(int bound) override;
    int64_t nextLong() override;
    float nextFloat() override;
    double nextDouble() override;
    bool nextBoolean() override;
    double nextGaussianDouble() override;

    void consumeCount(uint32_t count) override;
    std::unique_ptr<IRandom> fork() override;

    std::unique_ptr<IRandom> forBlockPos(const BlockPos&) const override;

private:
    uint64_t next(uint32_t bits);
    static uint64_t initialScramble(const uint64_t seed) {
        return (seed ^ MULTIPLIER) & MASK;
    };
};

#endif //SIMPLERANDOM_HPP
