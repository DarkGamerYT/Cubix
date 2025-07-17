#include "Mth.hpp"

#include <algorithm>
inline bool isSinTableEmpty() {
    return std::ranges::all_of(g_SinTable,
        [](const double v) { return v == 0.0; });
};

float Mth::sin(const double value)
{
    if (isSinTableEmpty())
        Mth::initMth();

    const int angle = static_cast<int>(value * 10430.378) & 0xFFFF;
    return g_SinTable[angle];
};

float Mth::cos(const double value)
{
    if (isSinTableEmpty())
        Mth::initMth();

    const int angle = static_cast<int>(value * 10430.378f + 16384.0f) & 0xFFFF;
    return g_SinTable[angle];
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

unsigned Mth::fastRandom()
{
    static int x1, x2, x3, x4;

    const int x0 = x1;
    x1 = x2;
    x2 = x3;
    x3 = x4;

    return (
        x4 = x4 ^ (static_cast<unsigned>(x4) >> 19) ^ x0 ^ (x0 << 11) ^ ((x0 ^ static_cast<unsigned>(x0 << 11)) >> 8)
    );
};