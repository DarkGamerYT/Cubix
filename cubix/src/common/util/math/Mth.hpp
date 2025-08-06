#ifndef MTH_HPP
#define MTH_HPP

#include <cmath>
#include <array>
#include <algorithm>
#include <mutex>

namespace Mth {
    constexpr double PI = 3.141592653589793;
    constexpr double TWO_PI = 2.0 * PI;
    constexpr int SIN_TABLE_SIZE = 65536;

    void initMth();

    float absDecrease(float value, float with, float min);
    float absMaxUnsigned(float a, float b);
    float absMax(float a, float b);

    float approach(float current, float target, float increment);

    inline float atan(const float x) {
        return std::atan(x);
    };

    inline float atan2(const float dy, const float dx) {
        return std::atan2(dy, dx);
    };

    inline float clamp(const float v, const float low, const float high) {
        return std::clamp(v, low, high);
    };

    inline int clamp(const int v, const int low, const int high) {
        return std::clamp(v, low, high);
    };

    float clampedLerp(float min, float max, float factor);
    float inverseLerp(float min, float max, float value);
    float clampedMap(float value, float fromMin, float fromMax, float toMin, float toMax);
    float map(float value, float fromMin, float fromMax, float toMin, float toMax);

    float wrapDegrees(float degrees);
    float degreesDifference(float angleA, float angleB);
    float lerpRotate(float from, float to, float factor);
    float snapRotationToCardinal(float degrees);

    float cos(double);
    float sin(double);

    inline float sqrt(const float value) {
        return std::sqrt(value);
    };

    int floor(double value);
    int ceil(double);

    template<typename T>
    static T abs(T value) {
        return std::abs(value);
    };

    uint32_t fastRandom();
};

#endif // !MTH_HPP
