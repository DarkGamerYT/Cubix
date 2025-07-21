#include "Vec2.hpp"
std::string Vec2::toString() const
{
    std::stringstream oss;
    oss << "Vec2(x: " << x << ", y: " << y << ")";
    return oss.str();
};