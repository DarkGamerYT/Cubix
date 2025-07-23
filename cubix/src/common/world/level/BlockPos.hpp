#ifndef BLOCKPOS_HPP
#define BLOCKPOS_HPP

#include <cstdint>
#include <sstream>
#include <string>

#include "../phys/Vec3.hpp"

class BlockPos
{
public:
    double x, y, z;

public:
    BlockPos() : x(0), y(0), z(0) {};
    BlockPos(const Vec3& vec)
        : x(vec.x), y(vec.y), z(vec.z) {};
    BlockPos(double x, double y, double z)
        : x(x), y(y), z(z) {};

    BlockPos above(int v = 1) { return { this->x, this->y + v, this->z }; };
    BlockPos below(int v = 1) { return { this->x, this->y - v, this->z }; };
    BlockPos north(int v = 1) { return { this->x, this->y, this->z - v }; };
    BlockPos south(int v = 1) { return { this->x, this->y, this->z + v }; };
    BlockPos east(int v = 1) { return { this->x + v, this->y, this->z }; };
    BlockPos west(int v = 1) { return { this->x - v, this->y, this->z }; };

    BlockPos center() { return { this->x + (float)0.5, this->y + (float)0.5, this->z + (float)0.5 }; };

    const int64_t randomSeed() const;
    const std::string toString() const;
};

#endif // !BLOCKPOS_HPP