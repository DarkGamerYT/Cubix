#include "BlockPos.hpp"
const int64_t BlockPos::randomSeed() const
{
    int64_t l = (int64_t)(3129871 * x) ^ (int64_t)y ^ (116129781 * (int64_t)z);
    return (l * l * 42317861 + l * 11) >> 16;
};

const std::string BlockPos::toString() const
{
    std::stringstream stream;
    stream << "BlockPos(";
    stream << std::to_string(this->x) << ",";
    stream << std::to_string(this->y) << ",";
    stream << std::to_string(this->z);
    stream << ")";

    return stream.str();
};