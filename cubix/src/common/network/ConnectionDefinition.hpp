#ifndef CONNECTIONDEFINITION_HPP
#define CONNECTIONDEFINITION_HPP

#include <string>

#include "PortPair.hpp"

struct ConnectionDefinition {
    std::string serverName;
    PortPair serverPorts;
    int maxPlayers = SharedConstants::NetworkMaxPlayers;
    bool isServerVisibleToLanDiscovery;

    CompressionType compressionType = CompressionType::Zlib;
    short compressionThreshold = 0;
};

#endif //CONNECTIONDEFINITION_HPP
