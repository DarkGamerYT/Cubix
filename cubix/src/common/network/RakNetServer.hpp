#pragma once
#include <memory>

#include "../../../src-deps/RakNet/Source/DS_Map.h"
#include "../../../src-deps/RakNet/Source/MessageIdentifiers.h"
#include "../../../src-deps/RakNet/Source/RakPeer.h"
#include "../../../src-deps/RakNet/Source/RakPeerInterface.h"

#include "NetworkServer.hpp"
#include "NetworkIdentifier.hpp"

class RakNetServer : public NetworkServer
{
private:
    std::mutex m_peerMutex;

public:
    RakNet::RakPeerInterface* m_pPeerInterface;
    RakNet::RakNetGUID m_Guid;
    RakNet::SocketDescriptor m_SocketDescriptor[2];

public:
    explicit RakNetServer(ServerNetworkHandler*);

    void startServer(PortPair ports, int maxPlayers) override;
    void stopServer() override;
    void update() override;
    void disconnectClient(const NetworkIdentifier&, SubClientId, DisconnectReason, bool skipMessage, const std::string&) override;

    void sendPacket(BinaryStream&, NetworkPeer::Reliability) override;
    void sendPacket(const NetworkIdentifier&, BinaryStream&, NetworkPeer::Reliability) override;
};