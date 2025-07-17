#ifndef NETWORKPEER_HPP
#define NETWORKPEER_HPP

#include <zlib/zlib.h>

#include "CompressionType.hpp"
#include "Packet.hpp"
#include "NetworkIdentifier.hpp"

#include "../util/BinaryStream.hpp"

class NetworkServer;
class NetworkPeer
{
private:

public:
    enum class Reliability : int {
        Unreliable          = 0,
        UnreliableSequenced = 1,
        Reliable            = 2,
        ReliableOrdered     = 3,
    };

protected:
    NetworkIdentifier m_NetworkIdentifier;
    NetworkServer* m_NetworkServer;

public:
    CompressionType m_Compression = CompressionType::Disabled;
    uint16_t m_CompressionThreshold = 0;

public:
    NetworkPeer() {};
    NetworkPeer(const NetworkIdentifier& networkIdentifier, NetworkServer* serverLocator)
        : m_NetworkIdentifier(networkIdentifier), m_NetworkServer(serverLocator) {};

    BinaryStream& receivePacket(BinaryStream&) const;
    void sendPacket(Packet&, SubClientId, NetworkPeer::Reliability = Reliability::ReliableOrdered) const;

    NetworkServer* getNetworkServer() const { return this->m_NetworkServer; };
    const NetworkIdentifier& getNetworkIdentifier() const { return this->m_NetworkIdentifier; };
    bool isCompressed() const { return this->m_Compression != CompressionType::Disabled; };
};

#endif // !NETWORKPEER_HPP
