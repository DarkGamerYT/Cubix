#include "SimpleRandom.hpp"
SimpleRandom::SimpleRandom() : mGaussianSource([this]() {
    return this->nextDouble();
}) {
    this->setSeed(LevelSeed64{});
};

SimpleRandom::SimpleRandom(const LevelSeed64& seed) : mGaussianSource([this]() {
    return this->nextDouble();
}) {
    this->setSeed(seed);
};

void SimpleRandom::setSeed(const LevelSeed64& seed) {
    this->mSeed = SimpleRandom::initialScramble(seed.getSeed());
};

uint64_t SimpleRandom::next(const uint32_t bits) {
    this->mSeed = (this->mSeed * MULTIPLIER + ADDEND) & MASK;
    return this->mSeed >> (48 - bits);
};

int SimpleRandom::nextInt() {
    return static_cast<int>(next(32));
};

int SimpleRandom::nextInt(const int bound) {
    if (bound <= 0)
        return 0;

    if ((bound & -bound) == bound) // Power of two
        return static_cast<int>((bound * static_cast<int64_t>(this->next(31))) >> 31);

    int bits, value;
    do {
        bits = static_cast<int>(this->next(31));
        value = bits % bound;
    } while (bits - value + (bound - 1) < 0);
    return value;
};

int64_t SimpleRandom::nextLong() {
    const uint64_t high = next(32);
    const uint64_t low = next(32);
    return static_cast<int64_t>((high << 32) | low);
};

float SimpleRandom::nextFloat() {
    return static_cast<float>(this->next(24)) / (1 << 24);
};

double SimpleRandom::nextDouble() {
    return static_cast<double>((this->next(26) << 27) + this->next(27)) / (1ULL << 53);
};

bool SimpleRandom::nextBoolean() {
    return this->next(1) != 0;
};

double SimpleRandom::nextGaussianDouble() {
    return this->mGaussianSource.nextGaussian();
};

void SimpleRandom::consumeCount(const uint32_t count) {
    for (uint32_t i = 0; i < count; ++i) {
        this->mSeed = (MULTIPLIER * this->mSeed + ADDEND) & MASK;
    };
};

std::unique_ptr<IRandom> SimpleRandom::fork() {
    const uint64_t seed1 = (MULTIPLIER * this->mSeed + ADDEND) & MASK;
    const uint64_t seed2 = (MULTIPLIER * seed1 + ADDEND) & MASK;
    this->mSeed = seed2;

    // Construct a nextLong-style 64-bit number from the two 48-bit seeds
    const uint64_t nextLong = (seed2 >> 16) + ((seed1 >> 16) << 32);

    LevelSeed64 newSeed{ (nextLong ^ MULTIPLIER) & MASK };
    return std::make_unique<SimpleRandom>(newSeed);
};

std::unique_ptr<IRandom> SimpleRandom::forBlockPos(const BlockPos& blockPos) const {
    const uint64_t value = this->mSeed ^ (static_cast<uint64_t>(blockPos.randomSeed()) >> 16);

    LevelSeed64 newSeed{ (value ^ MULTIPLIER) & MASK };
    return std::make_unique<SimpleRandom>(newSeed);
};