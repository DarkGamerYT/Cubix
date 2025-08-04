#include "ChunkPos.hpp"
std::string ChunkPos::toString() const
{
    std::stringstream stream;
    stream
        << "ChunkPos("
        << std::to_string(this->x) << ","
        << std::to_string(this->z)
        << ")";

    return stream.str();
};