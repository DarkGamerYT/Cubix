#include "Mth.hpp"

static std::array<double, Mth::SIN_TABLE_SIZE> gSinTable{};
static std::once_flag gSinTableInitFlag;

void Mth::initMth() {
    for (int i = 0; i < 65536; i++) {
        gSinTable[i] = std::sin(static_cast<double>(i) * PI * 2 / 65536);
    };
};

float Mth::absMaxUnsigned(const float a, const float b) {
    return std::fmax(std::fabs(a), std::fabs(b));
};

float Mth::absMax(const float a, const float b) {
    if (std::fabs(a) > std::fabs(b))
        return a;

    return b;
};

float Mth::approach(const float current, const float target, const float increment) {
    const float delta = target - current;
    const float absIncrement = std::fabs(increment);

    if (delta > absIncrement)
        return current + absIncrement;
    else if (delta < -absIncrement)
        return current - absIncrement;

    return target;
};

float Mth::clampedLerp(const float min, const float max, const float factor) {
    if (factor <= 0.0f)
        return min;
    if (factor >= 1.0f)
        return max;

    return min + (max - min) * factor;
};

float Mth::inverseLerp(const float min, const float max, const float value) {
    const float range = max - min;
    // Handle division by zero or a very small number
    if (std::abs(range) < 1e-7f)
        return (value < min) ? 0.0f : 1.0f;

    return (value - min) / range;
};

float Mth::clampedMap(const float value, const float fromMin, const float fromMax, const float toMin, const float toMax) {
    const float factor = Mth::inverseLerp(fromMin, fromMax, value);
    return Mth::clampedLerp(toMin, toMax, factor);
};

float Mth::map(const float value, const float fromMin, const float fromMax, const float toMin, const float toMax) {
    const float factor = Mth::inverseLerp(fromMin, fromMax, value);
    return toMin + (toMax - toMin) * factor;
};

float Mth::wrapDegrees(float degrees) {
    degrees = std::fmod(degrees + 180.0f, 360.0f);
    if (degrees < 0)
        degrees += 360.0f;

    return degrees - 180.0f;
};

float Mth::degreesDifference(const float angleA, const float angleB) {
    return Mth::wrapDegrees(angleA - angleB);
};

float Mth::lerpRotate(const float from, const float to, const float factor) {
    const float diff = Mth::wrapDegrees(to - from);
    return from + diff * factor;
};

float Mth::snapRotationToCardinal(const float degrees) {
    return std::round(degrees / 90.0f) * 90.0f;
};

float Mth::sin(const double value)
{
    std::call_once(gSinTableInitFlag, Mth::initMth);

    const int index = static_cast<int>(value * (SIN_TABLE_SIZE / TWO_PI));
    return static_cast<float>(gSinTable[index & (SIN_TABLE_SIZE - 1)]);
};

float Mth::cos(const double value)
{
    std::call_once(gSinTableInitFlag, Mth::initMth);

    const int index = static_cast<int>((value * (SIN_TABLE_SIZE / TWO_PI)) + (SIN_TABLE_SIZE / 4.0f));
    return static_cast<float>(gSinTable[index & (SIN_TABLE_SIZE - 1)]);
};

int Mth::floor(const double value)
{
    const int i = static_cast<int>(value);
    return value < static_cast<float>(i) ? (i - 1) : i;
};

int Mth::ceil(const double value)
{
    const int i = static_cast<int>(value);
    return value > static_cast<float>(i) ? (i + 1) : i;
};

inline uint32_t x = 0x075BCD15;   // 123456789
inline uint32_t y = 0x159A55E5;   // 362436069
inline uint32_t z = 0x1F123BB5;   // 521288629
inline uint32_t w = 0x05491333;   //  88675123

uint32_t Mth::fastRandom()
{
    const uint32_t v0 = x ^ (x << 11);
    x = y;
    y = z;
    z = w;

    const uint32_t mix = v0 ^ w ^ ((v0 ^ (w >> 11)) >> 8);
    w ^= mix;

    return mix;
};