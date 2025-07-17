#include "AppPlatform.hpp"
AppPlatform::AppPlatform()
{

};

AppPlatform::~AppPlatform()
{

};

void AppPlatform::crashOnPurpose() const
{
    volatile int* a = reinterpret_cast<volatile int*>(0xDEADC0DE);
    *a = 1;
};