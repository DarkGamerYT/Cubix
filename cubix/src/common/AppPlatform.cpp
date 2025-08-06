#include "AppPlatform.hpp"
AppPlatform::AppPlatform()
{
    Mth::initMth();
};

AppPlatform::~AppPlatform()
{

};

void AppPlatform::crashOnPurpose() const
{
    const auto a = reinterpret_cast<volatile int*>(0xDEADC0DE);
    *a = 1;
};