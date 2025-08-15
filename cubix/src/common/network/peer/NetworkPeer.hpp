#ifndef NETWORKPEER_HPP
#define NETWORKPEER_HPP

#include <utility>

#include "../connection/CompressionType.hpp"
#include "../Packet.hpp"
#include "NetworkIdentifier.hpp"

#include "../../util/BinaryStream.hpp"

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
    NetworkIdentifier mNetworkIdentifier;
    NetworkServer* mNetworkServer{};

public:
    CompressionType mCompression = CompressionType::Disabled;
    uint16_t mCompressionThreshold = 0;

public:
    NetworkPeer() = default;
    NetworkPeer(NetworkIdentifier networkIdentifier, NetworkServer* serverLocator)
        : mNetworkIdentifier(std::move(networkIdentifier)), mNetworkServer(serverLocator) {};

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
            const auto packetId = static_cast<uint16_t>(packet.getId());

            packetHeader |= (packetId & 0x03FF); // Packet ID (10 bits)
            packetHeader |= (static_cast<uint16_t>(subClientSenderId & 0x03) << 10); // Sender ID (2 bits)
            packetHeader |= (static_cast<uint16_t>(subClientTargetId & 0x03) << 12); // Target ID (2 bits)

            binaryStream.writeUnsignedVarInt(packetHeader);

            // Write packet data
            packet.write(binaryStream);

            dataStream.writeUnsignedVarInt(binaryStream.size());
            dataStream.writeBytes(binaryStream.data(), binaryStream.size());


            /*Logger::log(Logger::LogLevel::Debug,
                "Target: {} - {}: {}", static_cast<uint8_t>(subClientId), packet.getName(), binaryStream.toString());*/
        };

        (writePacket(args), ...);
        this->sendStream(dataStream, Reliability::ReliableOrdered);
    };

    NetworkServer* getNetworkServer() const { return this->mNetworkServer; };
    const NetworkIdentifier& getNetworkIdentifier() const { return this->mNetworkIdentifier; };
    bool isCompressed() const { return this->mCompression != CompressionType::Disabled; };

private:
    void sendStream(const BinaryStream&, NetworkPeer::Reliability = Reliability::ReliableOrdered) const;
};

#endif // !NETWORKPEER_HPP
