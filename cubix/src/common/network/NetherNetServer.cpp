#include "NetherNetServer.hpp"
#include "ServerNetworkHandler.hpp"
NetherNetServer::NetherNetServer(ServerNetworkHandler* networkHandler)
{
    this->m_Network = networkHandler;
    this->m_Identifier = NetworkIdentifier(0);
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
    this->m_Network->disconnectClient(
        networkIdentifier, subClientId,
        disconnectReason, skipMessage, message);
};

void NetherNetServer::update()
{

};

void NetherNetServer::sendPacket(BinaryStream& stream, const NetworkPeer::Reliability reliability)
{
    for (const auto &identifier: this->m_Network->getConnections() | std::views::keys)
    {
        this->sendPacket(identifier, stream, reliability);
    };
};
void NetherNetServer::sendPacket(const NetworkIdentifier& identifier, BinaryStream& stream, NetworkPeer::Reliability reliability)
{
    
};