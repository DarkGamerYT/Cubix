#include "MarsagliaPolarGaussian.hpp"
MarsagliaPolarGaussian::MarsagliaPolarGaussian(std::function<double()> nextDouble) {
    this->mNextDouble = std::move(nextDouble);
};

double MarsagliaPolarGaussian::nextGaussian() {
    if (this->mHasSpare)
    {
        this->mHasSpare = false;
        return this->mSpare;
    };

    double u, v, s;
    do {
        u = 2.0 * this->mNextDouble() - 1.0;
        v = 2.0 * this->mNextDouble() - 1.0;
        s = u * u + v * v;
    } while (s >= 1.0 || s == 0.0);

    const double multiplier = std::sqrt(-2.0 * std::log(s) / s);

    this->mSpare = v * multiplier;
    this->mHasSpare = true;
    return u * multiplier;
};