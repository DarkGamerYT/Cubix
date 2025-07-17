#pragma once
#include "../../../registry/BlockStateRegistry.hpp"

#include "../Block.hpp"

class LogBlock : public Block
{
public:
    LogBlock(const std::string& identifier);
    LogBlock(const std::string& identifier, int id);
};