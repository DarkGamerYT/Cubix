#ifndef AABB_HPP
#define AABB_HPP

#include <sstream>

#include "Vec3.hpp"

class AABB
{
public:
    Vec3 min, max;

public:
    AABB() : min(Vec3()), max(Vec3()) {};

    AABB(const double minX, const double minY, const double minZ, const double maxX, const double maxY, const double maxZ)
        : min(Vec3(minX, minY, minZ)), max(Vec3(maxX, maxY, maxZ)) {};

    AABB(const Vec3& min, const Vec3& max) : min(min), max(max) {};

    AABB(const Vec3& center, const double radius)
        : min(center - radius), max(center + radius) {};


    void set(const Vec3& min, const Vec3& max)
    {
        this->min = min;
        this->max = max;
    };

    void set(const AABB& other)
    {
        min = other.min;
        max = other.max;
    };
    
    void set(const double minX, const double minY, const double minZ, const double maxX, const double maxY, const double maxZ)
    {
        min.x = minX;
        min.y = minY;
        min.z = minZ;

        max.x = maxX;
        max.y = maxY;
        max.z = maxZ;
    };

    void expand(const Vec3& amount) {
        min = min - amount;
        max = max + amount;
    };

    AABB expanded(const Vec3& amount) const {
        return { min - amount, max + amount };
    };

    void move(const Vec3& offset)
    {
        min = min + offset;
        max = max + offset;
    };
    void move(double dx, double dy, double dz) {
        this->move({ dx, dy, dz });
    };

    AABB translated(const Vec3& offset) const
    {
        return { min + offset, max + offset };
    };

    AABB merge(const AABB& other) const
    {
        return { std::min(min, other.min), std::max(max, other.max) };
    };

    AABB grow(const Vec3& amount) const { return expanded(amount); };

    AABB cloneMove(const Vec3& offset) const { return translated(offset); };

    bool intersects(const AABB& other) const { return min <= other.max && max >= other.min; };
    bool contains(const AABB& other) const { return min <= other.min && max >= other.max; }

    static double distanceSquared(const AABB& aabb, const Vec3& point)
    {
        const double dx = std::max(aabb.min.x - point.x, 0.0) + std::max(point.x - aabb.max.x, 0.0);
        const double dy = std::max(aabb.min.y - point.y, 0.0) + std::max(point.y - aabb.max.y, 0.0);
        const double dz = std::max(aabb.min.z - point.z, 0.0) + std::max(point.z - aabb.max.z, 0.0);
        return (dx * dx + dy * dy + dz * dz);
    };
    static double distanceSquared(const AABB& a, const AABB& b)
    {
        return AABB::distanceSquared(a, b.getCenter());
    };
    static double distance(const AABB& aabb, const Vec3& point)
    {
        return std::sqrt(AABB::distanceSquared(aabb, point));
    };
    static double distance(const AABB& a, const AABB& b)
    {
        return std::sqrt(AABB::distanceSquared(a, b));
    };

    void centerAt(const Vec3& center)
    {
        Vec3 halfSize = this->getSize() * 0.5f;
        min = center - halfSize;
        max = center + halfSize;
    };

    Vec3 getCenter() const { return (min + max) * 0.5f; };
    Vec3 getSize() const { return max - min; };

    double getVolume() const
    {
        const Vec3& size = this->getSize();
        return size.x * size.y * size.z;
    };

    bool isEmpty() const
    {
        const Vec3& size = this->getSize();
        return size.x <= 0 || size.y <= 0 || size.z <= 0;
    };

    std::string toString() const;

    bool operator==(const AABB& other) const { return this->min == other.min && this->max == other.max; };
    bool operator!=(const AABB& other) const { return !(*this == other); };
};

#endif // !AABB_HPP