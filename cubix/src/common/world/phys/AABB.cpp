#include "AABB.hpp"
std::string AABB::toString() const
{
    std::stringstream oss;
    oss << "AABB(min: (" << min.x << ", " << min.y << ", " << min.z
        << "), max: (" << max.x << ", " << max.y << ", " << max.z << "))";
    return oss.str();
};