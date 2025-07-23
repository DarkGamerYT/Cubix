#ifndef NETWORKSERVER_HPP
#define NETWORKSERVER_HPP

#include <memory>
#include <thread>
#include <ranges>
#include <string>

#include "PortPair.hpp"
#include "Packet.hpp"
#include "NetworkPeer.hpp"
#include "NetworkIdentifier.hpp"
#include "../util/BinaryStream.hpp"
#include "../AppPlatform.hpp"
#include "../SharedConstants.hpp"
#include "../world/GameMode.hpp"
#include "../util/Logger.hpp"
#include "packets/DisconnectPacket.hpp"

class ServerNetworkHandler;
class NetworkServer
{
public:
    virtual ~NetworkServer() = default;

    std::string m_UnconnectedPong;
    ServerNetworkHandler* m_Network;
    NetworkIdentifier m_Identifier;

public:
    virtual void startServer(PortPair, int) = 0;
    virtual void stopServer() = 0;
    virtual void update() = 0;
    virtual void disconnectClient(const NetworkIdentifier&, SubClientId, DisconnectReason, bool skipMessage = false, const std::string& = "disconnectionScreen.noReason") = 0;

    virtual void sendPacket(BinaryStream&, NetworkPeer::Reliability) = 0;
    virtual void sendPacket(const NetworkIdentifier&, BinaryStream&, NetworkPeer::Reliability) = 0;
};

#endif // !NETWORKSERVER_HPP
