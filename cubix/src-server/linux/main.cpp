#include "../common/DedicatedServer.hpp"

#include "../../src/linux/AppPlatform_linux.hpp"

DedicatedServer gDedicatedServer;
inline AppPlatform_linux gAppPlatform;
int main(int argc, char* argv[])
{
    gDedicatedServer.start();
    gDedicatedServer.shutdown();
    std::cout << "Quit correctly." << std::endl;
};