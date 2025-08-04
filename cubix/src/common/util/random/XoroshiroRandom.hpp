#ifndef XOROSHIRORANDOM_HPP
#define XOROSHIRORANDOM_HPP

#include <bit>

#include "IRandom.hpp"
#include "IPositionalRandom.hpp"
#include "MarsagliaPolarGaussian.hpp"

#include "../../world/level/storage/LevelSeed128.hpp"

class XoroshiroRandom final : public IRandom, IPositionalRandom {
private:
    LevelSeed128 mSeed{};
    MarsagliaPolarGaussian mGaussianSource;

public:
    XoroshiroRandom();
    explicit XoroshiroRandom(const LevelSeed64& seed);
    explicit XoroshiroRandom(const LevelSeed128& seed);

    void setSeed(const LevelSeed64& seed);
    void setSeed(const LevelSeed128& seed);

    const LevelSeed128& getSeed128() const { return this->mSeed; };

    int nextInt(int bound) override;
    int nextInt() override;
    int64_t nextLong() override;
    float nextFloat() override;
    double nextDouble() override;
    bool nextBoolean() override;
    double nextGaussianDouble() override;

    void consumeCount(uint32_t count) override;
    std::unique_ptr<IRandom> fork() override;

    std::unique_ptr<IRandom> forBlockPos(const BlockPos&) const override;

private:
    uint64_t next();
};

#endif //XOROSHIRORANDOM_HPP
