#include "NetherNetServer.hpp"
#include "ServerNetworkHandler.hpp"
NetherNetServer::NetherNetServer(ServerNetworkHandler* networkHandler)
{
    this->mNetwork = networkHandler;
    this->mIdentifier = NetworkIdentifier(0);
};

void NetherNetServer::startServer(PortPair ports, int maxPlayers)
{
    
};

void NetherNetServer::stopServer()
{
    
};

void NetherNetServer::disconnectClient(
    const NetworkIdentifier& networkIdentifier,
    const SubClientId subClientId,
    const DisconnectReason disconnectReason,
    const bool skipMessage,
    const std::string& message
) {
    this->mNetwork->disconnectClient(
        networkIdentifier, subClientId,
        disconnectReason, skipMessage, message);
};

void NetherNetServer::update()
{

};

void NetherNetServer::sendPacket(BinaryStream& stream, const NetworkPeer::Reliability reliability)
{
    for (const auto &networkPeer: this->mNetwork->getConnections())
    {
        this->sendPacket(networkPeer->getNetworkIdentifier(), stream, reliability);
    };
};
void NetherNetServer::sendPacket(const NetworkIdentifier& identifier, BinaryStream& stream, NetworkPeer::Reliability reliability)
{
    
};