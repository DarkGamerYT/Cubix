#ifndef APPPLATFORM_HPP
#define APPPLATFORM_HPP

#include "util/math/Mth.hpp"

class AppPlatform
{
private:

public:
    AppPlatform();
    ~AppPlatform();

    void crashOnPurpose() const;
};

#endif // !APPPLATFORM_HPP