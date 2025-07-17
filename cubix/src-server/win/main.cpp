#include "../common/DedicatedServer.hpp"

#include "../../src/win/AppPlatform_win32.hpp"

DedicatedServer g_DedicatedServer;
inline AppPlatform_win32 g_AppPlatform;
int main(int argc, char* argv[])
{
    g_DedicatedServer.start();
    g_DedicatedServer.shutdown();
    std::cout << "Quit correctly." << std::endl;
};