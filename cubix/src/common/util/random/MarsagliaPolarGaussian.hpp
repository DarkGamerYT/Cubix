#ifndef MARSAGLIAPOLARGAUSSIAN_HPP
#define MARSAGLIAPOLARGAUSSIAN_HPP

#include <functional>

class MarsagliaPolarGaussian {
private:
    std::function<double()> mNextDouble;

    // Gaussian
    bool mHasSpare = false;
    double mSpare = 0.0;

public:
    explicit MarsagliaPolarGaussian(std::function<double()> nextDouble);

    double nextGaussian();
};

#endif //MARSAGLIAPOLARGAUSSIAN_HPP
