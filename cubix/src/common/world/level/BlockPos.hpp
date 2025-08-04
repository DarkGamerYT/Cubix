#ifndef BLOCKPOS_HPP
#define BLOCKPOS_HPP

#include <cstdint>
#include <sstream>
#include <string>

#include "../Facing.hpp"
#include "../phys/Vec3.hpp"

class BlockPos
{
public:
    int x, y, z;

public:
    BlockPos() : x(0), y(0), z(0) {};
    BlockPos(double x, double y, double z);
    BlockPos(float x, float y, float z);

    explicit BlockPos(const Vec3& vec) :
        x(static_cast<int>(std::floor(vec.x))),
        y(static_cast<int>(std::floor(vec.y))),
        z(static_cast<int>(std::floor(vec.z))) {};

    BlockPos above(const int steps = 1) const { return this->relative(Facing::Up, steps); };
    BlockPos below(const int steps = 1) const { return this->relative(Facing::Down, steps); };
    BlockPos north(const int steps = 1) const { return this->relative(Facing::North, steps); };
    BlockPos south(const int steps = 1) const { return this->relative(Facing::South, steps); };
    BlockPos east(const int steps = 1) const { return this->relative(Facing::East, steps); };
    BlockPos west(const int steps = 1) const { return this->relative(Facing::West, steps); };

    BlockPos relative(Facing facing, int steps) const;

    BlockPos center() const {
        return {
            static_cast<float>(this->x) + 0.5,
            static_cast<float>(this->y) + 0.5,
            static_cast<float>(this->z) + 0.5
        };
    };

    int64_t randomSeed() const;
    std::string toString() const;

    BlockPos operator+(const BlockPos& other) const { return BlockPos{ Vec3(x + other.x, y + other.y, z + other.z) }; };
    BlockPos operator-(const BlockPos& other) const { return BlockPos{ Vec3(x - other.x, y - other.y, z - other.z) }; };
    BlockPos operator*(const BlockPos& other) const { return BlockPos{ Vec3(x * other.x, y * other.y, z * other.z) }; };
    BlockPos operator/(const BlockPos& other) const { return BlockPos{ Vec3(x / other.x, y / other.y, z / other.z) }; };

    bool operator<(const BlockPos& other) const { return x < other.x && y < other.y && z < other.z; };
    bool operator<=(const BlockPos& other) const { return x <= other.x && y <= other.y && z <= other.z; };
    bool operator>(const BlockPos& other) const { return x > other.x && y > other.y && z > other.z; };
    bool operator>=(const BlockPos& other) const { return x >= other.x && y >= other.y && z >= other.z; };
    bool operator==(const BlockPos& other) const { return x == other.x && y == other.y && z == other.z; };
    bool operator!=(const BlockPos& other) const { return !(*this == other); };
};

#endif // !BLOCKPOS_HPP