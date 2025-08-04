#ifndef IPOSITIONALRANDOM_HPP
#define IPOSITIONALRANDOM_HPP

#include <memory>

#include "../../world/level/BlockPos.hpp"

#include "IRandom.hpp"

class IPositionalRandom {
public:
    virtual ~IPositionalRandom() = default;

    virtual std::unique_ptr<IRandom> forBlockPos(const BlockPos&) const = 0;
};

#endif //IPOSITIONALRANDOM_HPP
