#include "XoroshiroRandom.hpp"
XoroshiroRandom::XoroshiroRandom() : mGaussianSource([this]() {
    return this->nextDouble();
}) {
    this->setSeed(LevelSeed64{});
};

XoroshiroRandom::XoroshiroRandom(const LevelSeed64& seed) : mGaussianSource([this]() {
    return this->nextDouble();
}) {
    this->setSeed(seed);
};

XoroshiroRandom::XoroshiroRandom(const LevelSeed128& seed) : mGaussianSource([this]() {
    return this->nextDouble();
}) {
    this->setSeed(seed);
};

void XoroshiroRandom::setSeed(const LevelSeed64& seed) {
    const LevelSeed128 newSeed{ seed.getSeed() };
    this->setSeed(newSeed);
};

void XoroshiroRandom::setSeed(const LevelSeed128& seed) {
    auto [ low, high ] = seed.isZero()
        ? LevelSeed128{ 0x9E3779B97F4A7C15ULL, 0x6A09E667F3BCC909ULL }
        : seed;

    this->mSeed.low = low;
    this->mSeed.high = high;
};

uint64_t XoroshiroRandom::next() {
    const uint64_t result = std::rotl(this->mSeed.low + this->mSeed.high, 17) + this->mSeed.low;

    this->mSeed.high ^= this->mSeed.low;
    this->mSeed.low = std::rotl(this->mSeed.low, 49) ^ this->mSeed.high ^ (this->mSeed.high << 21);
    this->mSeed.high = std::rotl(this->mSeed.high, 28);

    return result;
};

int XoroshiroRandom::nextInt() {
    return static_cast<int32_t>(this->next() >> 33);
};

int XoroshiroRandom::nextInt(const int bound) {
    if (bound <= 0)
        return 0;

    const uint64_t threshold = -bound % bound;
    for (;;)
    {
        const auto r = static_cast<int>(this->next() >> 32);
        if (r < threshold)
            continue;

        return r % bound;
    };
};

int64_t XoroshiroRandom::nextLong() {
    return static_cast<int64_t>(this->next());
};

float XoroshiroRandom::nextFloat() {
    return static_cast<float>(this->next() >> 40) / static_cast<float>(1ULL << 24);
};

double XoroshiroRandom::nextDouble() {
    return static_cast<double>(this->next() >> 11) * (1.0 / (1ULL << 53));
};

bool XoroshiroRandom::nextBoolean() {
    return (this->next() & 1) != 0;
};

double XoroshiroRandom::nextGaussianDouble() {
    return this->mGaussianSource.nextGaussian();
};

void XoroshiroRandom::consumeCount(const uint32_t count) {
    for (uint32_t i = 0; i < count; ++i)
    {
        const uint64_t s0 = this->mSeed.low;
        const uint64_t s1 = this->mSeed.high;

        const uint64_t xor1 = s1 ^ s0;
        this->mSeed.low  = xor1 ^ (xor1 << 21) ^ std::rotr(s0, 15);
        this->mSeed.high = std::rotl(xor1, 28);
    };
};

std::unique_ptr<IRandom> XoroshiroRandom::fork() {
    const uint64_t s0 = this->mSeed.low;
    const uint64_t s1 = this->mSeed.high;

    const uint64_t a = std::rotl(s0 + s1, 17);
    const uint64_t b = a + s0;

    uint64_t newS1 = s1 ^ s0;
    const uint64_t newS0 = std::rotl(s0, 49) ^ newS1 ^ (newS1 << 21);
    newS1 = std::rotl(newS1, 28);

    this->mSeed.low = newS0;
    this->mSeed.high = newS1;

    uint64_t forkLow = b;
    uint64_t forkHigh = a + newS1;

    if ((forkLow | forkHigh) == 0)
    {
        forkLow  = 0x9E3779B97F4A7C15ULL;
        forkHigh = 0x6A09E667F3BCC909ULL;
    };

    LevelSeed128 newSeed{ forkLow, forkHigh };
    return std::make_unique<XoroshiroRandom>(newSeed);
};

std::unique_ptr<IRandom> XoroshiroRandom::forBlockPos(const BlockPos& blockPos) const {
    uint64_t seedLo = this->mSeed.low ^ (static_cast<uint64_t>(blockPos.randomSeed()) >> 16);
    uint64_t seedHi = this->mSeed.high;

    if ((seedLo | seedHi) == 0)
    {
        seedLo = 0x9E3779B97F4A7C15ULL;
        seedHi = 0x6A09E667F3BCC909ULL;
    };

    LevelSeed128 newSeed{ seedLo, seedHi };
    return std::make_unique<XoroshiroRandom>(newSeed);
};