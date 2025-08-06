#include "LogBlock.hpp"
LogBlock::LogBlock(const std::string& identifier)
    : Block(identifier)
{
    this->setState(BlockStateRegistry::PILLAR_AXIS);
};
LogBlock::LogBlock(const std::string& identifier, const int id)
    : Block(identifier, id)
{
    this->setState(BlockStateRegistry::PILLAR_AXIS);
};