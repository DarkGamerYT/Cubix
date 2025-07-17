#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <vector>

namespace Util
{
    struct Image {
        uint32_t width;
        uint32_t height;
        std::vector<uint8_t> data;
    };
};

#endif //IMAGE_HPP
