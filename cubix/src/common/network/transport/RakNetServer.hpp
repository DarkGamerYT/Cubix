#ifndef RAKNETSERVER_HPP
#define RAKNETSERVER_HPP

#include <memory>

#include "../../../../src-deps/RakNet/Source/DS_Map.h"
#include "../../../../src-deps/RakNet/Source/MessageIdentifiers.h"
#include "../../../../src-deps/RakNet/Source/RakPeer.h"
#include "../../../../src-deps/RakNet/Source/RakPeerInterface.h"

#include "NetworkServer.hpp"
#include "../peer/NetworkIdentifier.hpp"

class RakNetServer final : public NetworkServer
{
private:
    std::mutex mPeerMutex;

public:
    RakNet::RakPeerInterface* p_mPeerInterface;
    RakNet::RakNetGUID mGuid;
    RakNet::SocketDescriptor mSocketDescriptor[2];

public:
    explicit RakNetServer(ServerNetworkHandler*);

    void startServer(PortPair ports, int maxPlayers) override;
    void stopServer() override;
    void update() override;
    void disconnectClient(const NetworkIdentifier&, SubClientId, DisconnectReason, bool skipMessage, const std::string&) override;

    void sendPacket(BinaryStream&, NetworkPeer::Reliability) override;
    void sendPacket(const NetworkIdentifier&, BinaryStream&, NetworkPeer::Reliability) override;
};

#endif // !RAKNETSERVER_HPP