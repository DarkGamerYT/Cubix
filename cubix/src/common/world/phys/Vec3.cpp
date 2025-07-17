#include "Vec3.hpp"
Vec3 Vec3::normalized() const
{
    double magnitude = this->length();
    return *this / magnitude;
};

Vec3 Vec3::cross(const Vec3& a, const Vec3& b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
};

Vec3 Vec3::clamp(const Vec3& vec, const Vec3& min, const Vec3& max)
{
    double clampedX = std::clamp(vec.x, min.x, max.x);
    double clampedY = std::clamp(vec.y, min.y, max.y);
    double clampedZ = std::clamp(vec.z, min.z, max.z);
    return { clampedX, clampedY, clampedZ };
};

Vec3 Vec3::slerp(const Vec3& a, const Vec3& b, double s)
{
    double dot = Vec3::dot(a, b);
    double theta = std::acos(dot);
    double sinTheta = std::sin(theta);

    double factorA = std::sin((1.0 - s) * theta) / sinTheta;
    double factorB = std::sin(s * theta) / sinTheta;
    return (a * factorA) + (b * factorB);
};

std::string Vec3::toString() const
{
    std::stringstream oss;
    oss << "Vec3(x: " << x << ", y: " << y << ", z: " << z << ")";
    return oss.str();
};