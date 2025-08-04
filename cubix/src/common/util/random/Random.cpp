#include "Random.hpp"
Random::Random() : mGaussianSource([this]() {
    return this->nextDouble();
}) {
    this->_setSeed(std::random_device{}());
};

Random::Random(const uint32_t seed) : mGaussianSource([this]() {
    return this->nextDouble();
}) {
    this->_setSeed(seed);
};

void Random::_setSeed(uint32_t seed) {
    this->mSeed = seed;
    _mt[0] = seed;

    for (int i = 1; i < STATE_SIZE; ++i)
    {
        seed = i + 1812433253U * (seed ^ (seed >> 30));
        _mt[i] = seed;
    };

    _mti = STATE_SIZE;
    mInitedIdx = 398;
};

static constexpr uint32_t MAGIC[2] = { 0x0, 0x9908B0DF };
uint32_t Random::_genRandInt32() {
    constexpr uint32_t LOWER_MASK = 0x7FFFFFFF;
    constexpr int STATE_SIZE = 624;
    constexpr int TWIST_OFFSET = 397;
    constexpr uint32_t TEMPERING_MASK_B = 0xFF3A58AD;
    constexpr uint32_t TEMPERING_MASK_C = 0xFFFFDF8C;

    // Lazy state refresh logic (reinitialization if necessary)
    if (_mti >= STATE_SIZE + 1)
    {
        // Reinitialize with a default seed
        _mt[0] = 5489;
        for (_mti = 1; _mti < STATE_SIZE; ++_mti)
            _mt[_mti] = 1812433253UL * (_mt[_mti - 1] ^ (_mt[_mti - 1] >> 30)) + _mti;

        _mti = 0;
        mInitedIdx = STATE_SIZE;
    };

    // Twist step (one number per call)
    if (_mti == STATE_SIZE)
        _mti = 0;

    const int i = _mti;
    uint32_t y;

    if (i >= STATE_SIZE - TWIST_OFFSET)
    {
        if (i == STATE_SIZE - 1)
        {
            y = (_mt[STATE_SIZE - 1] ^ (_mt[STATE_SIZE - 1] ^ _mt[0]) & LOWER_MASK) >> 1;
            y ^= _mt[TWIST_OFFSET - 1];
            y ^= MAGIC[_mt[0] & 1];
        }
        else {
            y = (_mt[i] ^ (_mt[i] ^ _mt[i + 1]) & LOWER_MASK) >> 1;
            y ^= _mt[i - (STATE_SIZE - TWIST_OFFSET)];
            y ^= MAGIC[_mt[i + 1] & 1];
        };
    }
    else {
        y = (_mt[i] ^ (_mt[i] ^ _mt[i + 1]) & LOWER_MASK) >> 1;
        y ^= _mt[i + TWIST_OFFSET];
        y ^= MAGIC[_mt[i + 1] & 1];
    };

    _mt[i] = y;

    if (mInitedIdx < STATE_SIZE)
    {
        _mt[mInitedIdx] = mInitedIdx + 1812433253UL * (_mt[mInitedIdx] ^ (_mt[mInitedIdx] >> 30));
        ++mInitedIdx;
    };

    // Output current number and advance
    y = _mt[_mti++];

    // Tempering
    y ^= (y >> 11);
    y ^= (y << 7) & TEMPERING_MASK_B;
    y ^= (y << 15) & TEMPERING_MASK_C;
    y ^= (y >> 18);

    return y;
};

int Random::nextInt() {
    return static_cast<int>(this->_genRandInt32() >> 1);
};

int Random::nextInt(const int bound) {
    if (bound <= 0)
        return 0;

    const uint32_t r = this->_genRandInt32();
    const uint64_t m = static_cast<uint64_t>(r) * bound;
    return static_cast<int>(m >> 32);
};

int64_t Random::nextLong() {
    const uint32_t hi = this->_genRandInt32();
    const uint32_t lo = this->_genRandInt32();
    return (static_cast<int64_t>(hi) << 32) | lo;
};

float Random::nextFloat() {
    return static_cast<float>(this->_genRandInt32()) / static_cast<float>(UINT32_MAX);
};

double Random::nextDouble() {
    const uint64_t value = (static_cast<uint64_t>(this->_genRandInt32()) << 32) | this->_genRandInt32();
    return static_cast<double>(value) / static_cast<double>(UINT64_MAX);
};

bool Random::nextBoolean() {
    return (this->_genRandInt32() & 1) != 0;
};

double Random::nextGaussianDouble() {
    return this->mGaussianSource.nextGaussian();
};

void Random::consumeCount(const uint32_t count) {
    for (uint32_t i = 0; i < count; ++i) {
        this->_genRandInt32();
    };
};

std::unique_ptr<IRandom> Random::fork() {
    return std::make_unique<Random>(this->_genRandInt32());
};