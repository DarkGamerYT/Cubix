#ifndef DEDICATEDSERVER_HPP
#define DEDICATEDSERVER_HPP

#include <iostream>

#include "PropertiesSettings.hpp"
#include "../../src/common/util/Logger.hpp"
#include "../../src/common/util/UUID.hpp"
#include "../../src/common/SharedConstants.hpp"
#include "../../src/common/world/Difficulty.hpp"
#include "../../src/common/world/GameMode.hpp"

#include "../../src/common/server/ServerInstance.hpp"

class DedicatedServer
{
private:
    ServerInstance m_ServerInstance;

public:
    DedicatedServer();
    ~DedicatedServer();

    void initializeLogging();
    void start();
    void shutdown();
};

#endif // !DEDICATEDSERVER_HPP