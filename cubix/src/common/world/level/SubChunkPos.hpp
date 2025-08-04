#ifndef SUBCHUNKPOS_HPP
#define SUBCHUNKPOS_HPP

#include <cstdint>
#include <sstream>
#include <string>

#include "BlockPos.hpp"
#include "../phys/Vec3.hpp"

class SubChunkPos
{
public:
    int x, y, z;

public:
    SubChunkPos() : x(0), y(0), z(0) {};
    SubChunkPos(const int x, const int y, const int z)
        : x(x), y(y), z(z) {};

    explicit SubChunkPos(const Vec3& vec) :
        x(static_cast<int>(std::floor(vec.x)) >> 4),
        y(static_cast<int>(std::floor(vec.y)) >> 4),
        z(static_cast<int>(std::floor(vec.z)) >> 4) {};

    explicit SubChunkPos(const BlockPos& pos) :
        x(static_cast<int>(pos.x) >> 4),
        y(static_cast<int>(pos.y) >> 4),
        z(static_cast<int>(pos.z) >> 4) {};

    SubChunkPos above(const int steps = 1) const { return this->relative(Facing::Up, steps); };
    SubChunkPos below(const int steps = 1) const { return this->relative(Facing::Down, steps); };
    SubChunkPos north(const int steps = 1) const { return this->relative(Facing::North, steps); };
    SubChunkPos south(const int steps = 1) const { return this->relative(Facing::South, steps); };
    SubChunkPos east(const int steps = 1) const { return this->relative(Facing::East, steps); };
    SubChunkPos west(const int steps = 1) const { return this->relative(Facing::West, steps); };

    SubChunkPos relative(Facing facing, int steps) const;

    int64_t randomSeed() const;
    std::string toString() const;

    SubChunkPos operator+(const SubChunkPos& other) const { return { x + other.x, y + other.y, z + other.z }; };
    SubChunkPos operator-(const SubChunkPos& other) const { return { x - other.x, y - other.y, z - other.z }; };
    SubChunkPos operator*(const SubChunkPos& other) const { return { x * other.x, y * other.y, z * other.z }; };
    SubChunkPos operator/(const SubChunkPos& other) const { return { x / other.x, y / other.y, z / other.z }; };

    bool operator<(const SubChunkPos& other) const { return x < other.x && y < other.y && z < other.z; };
    bool operator<=(const SubChunkPos& other) const { return x <= other.x && y <= other.y && z <= other.z; };
    bool operator>(const SubChunkPos& other) const { return x > other.x && y > other.y && z > other.z; };
    bool operator>=(const SubChunkPos& other) const { return x >= other.x && y >= other.y && z >= other.z; };
    bool operator==(const SubChunkPos& other) const { return x == other.x && y == other.y && z == other.z; };
    bool operator!=(const SubChunkPos& other) const { return !(*this == other); };
};

#endif // !SUBCHUNKPOS_HPP