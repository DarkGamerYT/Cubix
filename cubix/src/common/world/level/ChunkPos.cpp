#include "ChunkPos.hpp"
const std::string ChunkPos::toString() const
{
    std::stringstream stream;
    stream << "ChunkPos(";
    stream << std::to_string(this->x) << ",";
    stream << std::to_string(this->z);
    stream << ")";

    return stream.str();
};