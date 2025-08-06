#include "Color.hpp"
namespace Util
{
    std::string Color::toHexString() const
    {
        const uint32_t color =
            (static_cast<uint32_t>(this->r * 255) << 24)
            | (static_cast<uint32_t>(this->g * 255) << 16)
            | (static_cast<uint32_t>(this->b * 255) << 8)
            | static_cast<uint32_t>(this->a * 255);

        std::stringstream stream;
        stream << "#" << std::hex << std::setw(8) << std::setfill('0') << color;
        return stream.str();
    };

    Color Color::fromHexString(const std::string& value)
    {
        const std::string& hex = (value[0] == '#' ? value.substr(1) : value);
        if (hex.size() != 8)
            return Util::Color{ 0, 0, 0, 0 };

        const float r = static_cast<float>(std::stoi(hex.substr(0, 2), nullptr, 16)) / 255.0f;
        const float g = static_cast<float>(std::stoi(hex.substr(2, 2), nullptr, 16)) / 255.0f;
        const float b = static_cast<float>(std::stoi(hex.substr(4, 2), nullptr, 16)) / 255.0f;
        const float a = static_cast<float>(std::stoi(hex.substr(6, 2), nullptr, 16)) / 255.0f;

        return Util::Color{ r, g, b, a };
    };

    uint32_t Color::encode() const {
        return (static_cast<uint32_t>(this->r * 255) << 24)
            | (static_cast<uint32_t>(this->g * 255) << 16)
            | (static_cast<uint32_t>(this->b * 255) << 8)
            | static_cast<uint32_t>(this->a * 255);
    };

    Color Color::decode(const uint32_t value) {
        const float r = static_cast<float>((value >> 24) & 0xFF) / 255.0f;
        const float g = static_cast<float>((value >> 16) & 0xFF) / 255.0f;
        const float b = static_cast<float>((value >> 8) & 0xFF) / 255.0f;
        const float a = static_cast<float>(value & 0xFF) / 255.0f;

        return Util::Color{ r, g, b, a };
    };
};