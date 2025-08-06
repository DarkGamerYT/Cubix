#pragma once
#include "../../../registry/BlockStateRegistry.hpp"

#include "../Block.hpp"

class LogBlock : public Block
{
public:
    LogBlock(const std::string& identifier, int id);
    explicit LogBlock(const std::string& identifier);
};