#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <sstream>
#include <string>

namespace Util
{
    class Color
    {
    public:
        float r, g, b, a;

    public:
        explicit Color(
            const float red = 0,
            const float green = 0,
            const float blue = 0,
            const float alpha = 0
        ) : r(red), g(green), b(blue), a(alpha) {};

        uint32_t encode() const;
        static Color decode(uint32_t);

        std::string toHexString() const;
        static Color fromHexString(const std::string&);
    };
};

#endif // !COLOR_HPP