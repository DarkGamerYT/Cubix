#include "../common/DedicatedServer.hpp"

#include "../../src/win/AppPlatform_win32.hpp"

DedicatedServer gDedicatedServer;
inline AppPlatform_win32 gAppPlatform;
int main(int argc, char* argv[])
{
    gDedicatedServer.start();
    gDedicatedServer.shutdown();
    std::cout << "Quit correctly." << std::endl;
};