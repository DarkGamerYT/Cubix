#ifndef VEC3_HPP
#define VEC3_HPP

#include <sstream>
#include <algorithm>
#include <cstdint>
#include <cmath>

class Vec3
{
public:
    double x, y, z;

public:
    Vec3() : x(0), y(0), z(0) {};
    Vec3(double x, double y, double z)
        : x(x), y(y), z(z) {};

    double lengthSquared() const
    {
        return ((x * x) + (y * y) + (z * z));
    };
    double length() const
    {
        return std::sqrt(this->lengthSquared());
    };
    Vec3 normalized() const;

    Vec3 abs() const
    {
        return { std::abs(x), std::abs(y), std::abs(z) };
    };
    Vec3 floor() const
    {
        return { std::floor(x), std::floor(y), std::floor(z) };
    };
    Vec3 ceil() const
    {
        return { std::ceil(x), std::ceil(y), std::ceil(z) };
    };
    Vec3 round() const
    {
        return { std::round(x), std::round(y), std::round(z) };
    };

    static double distanceSquared(const Vec3& a, const Vec3& b) { return (a - b).lengthSquared(); };
    static double distance(const Vec3& a, const Vec3& b) { return std::sqrt(distanceSquared(a, b)); }
    static Vec3 cross(const Vec3&, const Vec3&);
    static Vec3 clamp(const Vec3&, const Vec3&, const Vec3&);
    static double dot(const Vec3& a, const Vec3& b)
    {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    };
    static Vec3 lerp(const Vec3& a, const Vec3& b, double t)
    {
        return a + (b - a) * t;
    };
    static Vec3 slerp(const Vec3&, const Vec3&, double);

    std::string toString() const;

    Vec3 operator+(double scalar) const { return { x + scalar, y + scalar, z + scalar }; };
    Vec3 operator+(const Vec3& other) const { return { x + other.x, y + other.y, z + other.z }; };
    Vec3 operator-(double scalar) const { return { x - scalar, y - scalar, z - scalar }; };
    Vec3 operator-(const Vec3& other) const { return { x - other.x, y - other.y, z - other.z }; };
    Vec3 operator*(double scalar) const { return { x * scalar, y * scalar, z * scalar }; };
    Vec3 operator*(const Vec3& other) const { return { x * other.x, y * other.y, z * other.z }; };
    Vec3 operator/(double scalar) const { return { x / scalar, y / scalar, z / scalar }; };
    Vec3 operator/(const Vec3& other) const { return { x / other.x, y / other.y, z / other.z }; };
    
    bool operator<(const Vec3& other) const { return x < other.x && y < other.y && z < other.z; };
    bool operator<=(const Vec3& other) const { return x <= other.x && y <= other.y && z <= other.z; };
    bool operator>(const Vec3& other) const { return x > other.x && y > other.y && z > other.z; };
    bool operator>=(const Vec3& other) const { return x >= other.x && y >= other.y && z >= other.z; };
    bool operator==(const Vec3& other) const { return x == other.x && y == other.y && z == other.z; };
    bool operator!=(const Vec3& other) const { return !(*this == other); };
};

#endif // !VEC3_HPP