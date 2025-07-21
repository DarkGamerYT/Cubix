#ifndef NETWORKPEER_HPP
#define NETWORKPEER_HPP

#include <zlib/zlib.h>
#include <snappy/snappy.h>

#include "CompressionType.hpp"
#include "Packet.hpp"
#include "NetworkIdentifier.hpp"

#include "../util/BinaryStream.hpp"

template<typename T>
concept IsNetworkPacket = std::is_base_of_v<Packet, std::decay_t<T>>;

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

    template <typename... Args>
    requires (IsNetworkPacket<Args> && ...)
    void sendPacket(SubClientId subClientId, Args& ...args) const {
        BinaryStream dataStream;

        constexpr uint8_t subClientSenderId = 0;
        const auto subClientTargetId = static_cast<uint8_t>(subClientId);

        auto writePacket = [&](auto& packet) {
            BinaryStream binaryStream{};

            uint16_t packetHeader = 0;
            const uint16_t packetId = static_cast<uint16_t>(packet.getId());

            packetHeader |= (packetId & 0x03FF); // Packet ID (10 bits)
            packetHeader |= (static_cast<uint16_t>(subClientSenderId & 0x03) << 10); // Sender ID (2 bits)
            packetHeader |= (static_cast<uint16_t>(subClientTargetId & 0x03) << 12); // Target ID (2 bits)

            binaryStream.writeUnsignedVarInt(packetHeader);

            // Write packet data
            packet.write(binaryStream);

            dataStream.writeUnsignedVarInt(binaryStream.size());
            dataStream.writeBytes(binaryStream.data(), binaryStream.size());
        };

        (writePacket(args), ...);
        this->sendStream(dataStream, Reliability::ReliableOrdered);
    };

    NetworkServer* getNetworkServer() const { return this->m_NetworkServer; };
    const NetworkIdentifier& getNetworkIdentifier() const { return this->m_NetworkIdentifier; };
    bool isCompressed() const { return this->m_Compression != CompressionType::Disabled; };

private:
    void sendStream(const BinaryStream&, NetworkPeer::Reliability = Reliability::ReliableOrdered) const;
};

#endif // !NETWORKPEER_HPP
