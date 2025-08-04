#ifndef CHUNKPOS_HPP
#define CHUNKPOS_HPP

#include <cstdint>
#include <sstream>
#include <string>

#include "BlockPos.hpp"
#include "../phys/Vec3.hpp"

class ChunkPos
{
public:
    int x, z;

public:
    ChunkPos() : x(0), z(0) {};
    explicit ChunkPos(const Vec3& vec)
        : x(static_cast<int>(vec.x) >> 4), z(static_cast<int>(vec.z) >> 4) {};
    explicit ChunkPos(const BlockPos& pos)
        : x(static_cast<int>(pos.x) >> 4), z(static_cast<int>(pos.z) >> 4) {};
    ChunkPos(const int x, const int z)
        : x(x), z(z) {};

    std::string toString() const;

    ChunkPos operator+(const ChunkPos& other) const { return { x + other.x, z + other.z }; };
    ChunkPos operator-(const ChunkPos& other) const { return { x - other.x, z - other.z }; };
    ChunkPos operator*(const ChunkPos& other) const { return { x * other.x, z * other.z }; };
    ChunkPos operator/(const ChunkPos& other) const { return { x / other.x, z / other.z }; };

    bool operator<(const ChunkPos& other) const { return x < other.x && z < other.z; };
    bool operator<=(const ChunkPos& other) const { return x <= other.x && z <= other.z; };
    bool operator>(const ChunkPos& other) const { return x > other.x && z > other.z; };
    bool operator>=(const ChunkPos& other) const { return x >= other.x && z >= other.z; };
    bool operator==(const ChunkPos& other) const { return x == other.x && z == other.z; };
    bool operator!=(const ChunkPos& other) const { return !(*this == other); };
};

#endif // !CHUNKPOS_HPP