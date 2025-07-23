#ifndef CHUNKPOS_HPP
#define CHUNKPOS_HPP

#include <cstdint>
#include <sstream>
#include <string>

class ChunkPos
{
public:
    int x, z;

public:
    ChunkPos() : x(0), z(0) {};
    ChunkPos(int x, int z)
        : x(x), z(z) {};

    const std::string toString() const;
};

#endif // !CHUNKPOS_HPP