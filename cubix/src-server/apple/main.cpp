#include "../common/DedicatedServer.hpp"

#include "../../src/apple/AppPlatform_apple.hpp"

DedicatedServer gDedicatedServer;
inline AppPlatform_apple gAppPlatform;
int main(int argc, char* argv[])
{
    gDedicatedServer.start();
    gDedicatedServer.shutdown();
    std::cout << "Quit correctly." << std::endl;
};