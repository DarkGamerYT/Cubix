#ifndef IRANDOM_HPP
#define IRANDOM_HPP

#include <memory>
#include <cmath>
#include <random>

class IRandom {
public:
    virtual ~IRandom() = default;

    virtual int nextInt(int bound) = 0;
    virtual int nextInt() = 0;
    virtual int64_t nextLong() = 0;
    virtual float nextFloat() = 0;
    virtual double nextDouble() = 0;
    virtual bool nextBoolean() = 0;
    virtual double nextGaussianDouble() = 0;

    virtual void consumeCount(uint32_t) = 0;
    virtual std::unique_ptr<IRandom> fork() = 0;
};

#endif //IRANDOM_HPP