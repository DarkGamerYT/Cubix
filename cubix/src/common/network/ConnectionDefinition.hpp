#ifndef CONNECTIONDEFINITION_HPP
#define CONNECTIONDEFINITION_HPP

#include <string>

#include "PortPair.hpp"

struct ConnectionDefinition {
    std::string serverName;
    int maxPlayers;
    PortPair serverPorts;
    bool isVisibleToLan;
    bool useOnlineAuthentication;
};

#endif //CONNECTIONDEFINITION_HPP
