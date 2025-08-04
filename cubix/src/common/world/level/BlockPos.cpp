#include "BlockPos.hpp"
BlockPos::BlockPos(const double x, const double y, const double z) {
    this->x = static_cast<int>(std::floor(x));
    this->y = static_cast<int>(std::floor(y));
    this->z = static_cast<int>(std::floor(z));
};

BlockPos::BlockPos(const float x, const float y, const float z) {
    this->x = static_cast<int>(std::floor(x));
    this->y = static_cast<int>(std::floor(y));
    this->z = static_cast<int>(std::floor(z));
};

BlockPos BlockPos::relative(const Facing facing, const int steps) const {
    int newX = this->x;
    int newY = this->y;
    int newZ = this->z;

    switch (facing)
    {
        case Facing::Down:
            newY -= steps; break;
        case Facing::Up:
            newY += steps; break;
        case Facing::North:
            newZ -= steps; break;
        case Facing::South:
            newZ += steps; break;
        case Facing::West:
            newX -= steps; break;
        case Facing::East:
            newX += steps; break;

        default:
            break;
    };

    return BlockPos{ Vec3(newX, newY, newZ) };
};

int64_t BlockPos::randomSeed() const
{
    const int64_t lx = static_cast<int64_t>(3129871) * x;
    const int64_t lz = static_cast<int64_t>(116129781) * z;
    const int64_t value = static_cast<int64_t>(y) ^ lx ^ lz;

    return value * (42317861 * value + 11);
};

std::string BlockPos::toString() const
{
    std::stringstream stream;
    stream
        << "BlockPos("
        << std::to_string(this->x) << ","
        << std::to_string(this->y) << ","
        << std::to_string(this->z)
        << ")";

    return stream.str();
};