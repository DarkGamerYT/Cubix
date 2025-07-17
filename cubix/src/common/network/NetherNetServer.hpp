#pragma once
#include <memory>

#include "NetworkServer.hpp"
#include "NetworkIdentifier.hpp"

class NetherNetServer : public NetworkServer
{
public:

public:
    explicit NetherNetServer(ServerNetworkHandler*);

    void startServer(PortPair ports, int maxPlayers) override;
    void stopServer() override;
    void update() override;
    void disconnectClient(const NetworkIdentifier&, SubClientId, DisconnectReason, bool skipMessage, const std::string&) override;

    void sendPacket(BinaryStream&, NetworkPeer::Reliability) override;
    void sendPacket(const NetworkIdentifier&, BinaryStream&, NetworkPeer::Reliability) override;
};