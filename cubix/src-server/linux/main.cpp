#include "../common/DedicatedServer.hpp"

#include "../../src/linux/AppPlatform_linux.hpp"

DedicatedServer g_DedicatedServer;
inline AppPlatform_linux g_AppPlatform;
int main(int argc, char* argv[])
{
    g_DedicatedServer.start();
    g_DedicatedServer.shutdown();
    std::cout << "Quit correctly." << std::endl;
};