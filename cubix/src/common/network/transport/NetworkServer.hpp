#ifndef NETWORKSERVER_HPP
#define NETWORKSERVER_HPP

#include <memory>
#include <thread>
#include <ranges>
#include <string>

#include "PortPair.hpp"
#include "../Packet.hpp"
#include "../peer/NetworkPeer.hpp"
#include "../peer/NetworkIdentifier.hpp"
#include "../../util/BinaryStream.hpp"
#include "../../AppPlatform.hpp"
#include "../../SharedConstants.hpp"
#include "../../world/GameMode.hpp"
#include "../../util/Logger.hpp"
#include "../packets/DisconnectPacket.hpp"

class ServerNetworkHandler;
class NetworkServer
{
public:
    virtual ~NetworkServer() = default;

    std::string mUnconnectedPong;
    ServerNetworkHandler* mNetwork;
    NetworkIdentifier mIdentifier;

public:
    virtual void startServer(PortPair, int) = 0;
    virtual void stopServer() = 0;
    virtual void update() = 0;
    virtual void disconnectClient(const NetworkIdentifier&, SubClientId, DisconnectReason, bool skipMessage = false, const std::string& = "disconnectionScreen.noReason") = 0;

    virtual void sendPacket(BinaryStream&, NetworkPeer::Reliability) = 0;
    virtual void sendPacket(const NetworkIdentifier&, BinaryStream&, NetworkPeer::Reliability) = 0;
};

#endif // !NETWORKSERVER_HPP
