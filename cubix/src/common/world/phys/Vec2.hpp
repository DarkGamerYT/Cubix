#ifndef VEC2_HPP
#define VEC2_HPP

#include <sstream>
#include <algorithm>
#include <cstdint>
#include <cmath>

class Vec2
{
public:
    double x, y;

public:
    Vec2() : x(0), y(0) {};
    Vec2(const double x, const double y)
        : x(x), y(y) {};

    std::string toString() const;

    Vec2 operator+(const double scalar) const { return { x + scalar, y + scalar }; };
    Vec2 operator+(const Vec2& other) const { return { x + other.x, y + other.y }; };
    Vec2 operator-(const double scalar) const { return { x - scalar, y - scalar }; };
    Vec2 operator-(const Vec2& other) const { return { x - other.x, y - other.y }; };
    Vec2 operator*(const double scalar) const { return { x * scalar, y * scalar }; };
    Vec2 operator*(const Vec2& other) const { return { x * other.x, y * other.y }; };
    Vec2 operator/(const double scalar) const { return { x / scalar, y / scalar }; };
    Vec2 operator/(const Vec2& other) const { return { x / other.x, y / other.y }; };
    
    bool operator<(const Vec2& other) const { return x < other.x && y < other.y; };
    bool operator<=(const Vec2& other) const { return x <= other.x && y <= other.y; };
    bool operator>(const Vec2& other) const { return x > other.x && y > other.y; };
    bool operator>=(const Vec2& other) const { return x >= other.x && y >= other.y; };
    bool operator==(const Vec2& other) const { return x == other.x && y == other.y; };
    bool operator!=(const Vec2& other) const { return !(*this == other); };
};

#endif // !VEC2_HPP