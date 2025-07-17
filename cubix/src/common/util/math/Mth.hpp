#ifndef MTH_HPP
#define MTH_HPP

#include <cmath>

constexpr auto PI = 3.141592653589793;
inline double g_SinTable[65536];
namespace Mth {
    static void initMth() {
        for (int i = 0; i < 65536; i++) {
            g_SinTable[i] = std::sin(static_cast<double>(i) * PI * 2 / 65536);
        };
    };

    static float cos(double);
    static float sin(double);

    static float sqrt(const double value) { return std::sqrt(value); };
    static int floor(double value);
    static int ceil(double);

    template<typename T>
    static T abs(T value) {
        return std::abs(value);
    };

    static unsigned fastRandom();
};

#endif // !MTH_HPP
