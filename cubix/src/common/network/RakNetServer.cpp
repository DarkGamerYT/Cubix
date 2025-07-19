#include "RakNetServer.hpp"
#include "ServerNetworkHandler.hpp"
RakNetServer::RakNetServer(ServerNetworkHandler* networkHandler)
{
    this->m_pPeerInterface = RakNet::RakPeerInterface::GetInstance();
    this->m_Guid = this->m_pPeerInterface->GetMyGUID();

    this->m_Network = networkHandler;
    this->m_Identifier = NetworkIdentifier(this->m_Guid);
};

void RakNetServer::startServer(PortPair ports, int maxPlayers)
{
    constexpr int socketCount = RAKNET_SUPPORT_IPV6 ? 2 : 1;
    this->m_SocketDescriptor[0].socketFamily = AF_INET;
    this->m_SocketDescriptor[0].port = ports.mPortV4;
#if RAKNET_SUPPORT_IPV6
    this->m_SocketDescriptor[1].socketFamily = AF_INET6;
    this->m_SocketDescriptor[1].port = ports.mPortV6;
#endif

    switch (this->m_pPeerInterface->Startup(maxPlayers, this->m_SocketDescriptor, socketCount))
    {
        case RakNet::RAKNET_STARTED: {
            this->m_pPeerInterface->SetMaximumIncomingConnections(maxPlayers);

            Logger::log(Logger::LogLevel::Info,
                "IPv4 supported, port: {}: Used for gameplay {}",
                    ports.mPortV4, (ports.mPortV4 == 19132) ? "and LAN discovery" : "");

        #if RAKNET_SUPPORT_IPV6 == 1
            Logger::log(Logger::LogLevel::Info, "IPv6 supported, port: {}: Used for gameplay", ports.mPortV6);
        #endif

            Logger::log(Logger::LogLevel::Info, "Server started.");

            // Server announcement
            std::thread([](const RakNetServer* pServerLocator) {
                while (
                    pServerLocator->m_pPeerInterface != nullptr
                    && pServerLocator->m_pPeerInterface->IsActive()
                ) {
                    const std::string& message = pServerLocator->m_UnconnectedPong;
                    if (!message.empty())
                    {
                        pServerLocator->m_pPeerInterface->SetOfflinePingResponse(message.c_str(), static_cast<unsigned int>(message.size()));
                    };

                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                };
            }, this).detach();
            break;
        };
        case RakNet::SOCKET_PORT_ALREADY_IN_USE: {
            Logger::log(Logger::LogLevel::Error,
                "Port [{}] may be in use by another process. Free up the port or use alternate ports for server", ports.mPortV4);
        #if RAKNET_SUPPORT_IPV6 == 1
            Logger::log(Logger::LogLevel::Error,
                "Port [{}] may be in use by another process. Free up the port or use alternate ports for server", ports.mPortV6);
        #endif

            this->m_Network->shutdown();
            break;
        };
        default: {
            break;
        };
    };
};

void RakNetServer::stopServer()
{
    std::lock_guard<std::mutex> lock(this->m_peerMutex);
    if (this->m_pPeerInterface != nullptr)
    {
        {
            // Drain packets
            RakNet::Packet* packet = nullptr;
            while ((packet = this->m_pPeerInterface->Receive()) != nullptr)
                this->m_pPeerInterface->DeallocatePacket(packet);
        };

        this->m_pPeerInterface->Shutdown(1);
        RakNet::RakPeerInterface::DestroyInstance(this->m_pPeerInterface);
        this->m_pPeerInterface = nullptr;
    };
};

void RakNetServer::disconnectClient(
    const NetworkIdentifier& networkIdentifier,
    const SubClientId subClientId,
    const DisconnectReason disconnectReason,
    const bool skipMessage,
    const std::string& message
) {
    this->m_Network->disconnectClient(
        networkIdentifier, subClientId,
        disconnectReason, skipMessage, message);
    this->m_pPeerInterface->CloseConnection(networkIdentifier.m_Guid, true);
};

void RakNetServer::update()
{
    std::lock_guard<std::mutex> lock(this->m_peerMutex);
    if (this->m_pPeerInterface == nullptr)
        return;

    RakNet::Packet* packet = nullptr;
    while ((packet = this->m_pPeerInterface->Receive()) != nullptr)
    {
        const uint8_t packetId = packet->data[0];
        NetworkIdentifier networkIdentifier(packet->guid);
        switch (packetId)
        {
            // Minecraft Packets
            case 0xFE:
            {
                if (this->m_pPeerInterface->GetConnectionState(networkIdentifier.m_Guid) != RakNet::ConnectionState::IS_CONNECTED)
                    return;

                const auto& connections = this->m_Network->getConnections();
                if (!connections.contains(networkIdentifier))
                    continue;

                const std::shared_ptr<NetworkPeer>& networkPeer = connections.at(networkIdentifier);

                std::vector bitStream(packet->data, packet->data + packet->length);
                bitStream.erase(bitStream.begin());

                BinaryStream stream(bitStream);
                networkPeer->receivePacket(stream);

                while (true)
                    try
                    {
                        if (stream.bytesLeft() == 0)
                            break;

                        const uint32_t payloadSize = stream.readUnsignedVarInt();
                        if (payloadSize < 1)
                            continue;

                        if (stream.bytesLeft() < payloadSize)
                        {
                            Logger::log(Logger::LogLevel::Error,
                                "Payload size of {} is larger than what's left: {}", payloadSize, stream.bytesLeft());
                            continue;
                        };

                        using difference = std::vector<unsigned char>::difference_type;
                        const auto start = stream.m_Stream.begin() + static_cast<difference>(stream.m_ReadPos);
                        const auto end = std::next(start, payloadSize);

                        std::vector<uint8_t> payload{ start, end };
                        stream.m_ReadPos += payloadSize;

                        BinaryStream packetStream(payload);
                        this->m_Network->handle(networkIdentifier, packetStream);
                    }
                    catch (...)
                    {
                        this->disconnectClient(networkIdentifier, SubClientId::PrimaryClient,
                            DisconnectReason::BadPacket,
                            false, "%disconnectionScreen.badPacket");
                    };
                break;
            };

            case ID_NEW_INCOMING_CONNECTION:
            {
                this->m_Network->onConnect(networkIdentifier);

                Logger::log(Logger::LogLevel::Debug,
                    "Incoming connection. ServerID: raknet:{}, ClientID: raknet:{}", this->m_Guid.g, packet->guid.g);
                break;
            };

            case ID_CONNECTION_LOST:
            case ID_CONNECTION_ATTEMPT_FAILED:
            case ID_DISCONNECTION_NOTIFICATION:
            {
                this->m_Network->onDisconnect(networkIdentifier);
                break;
            };

            /*case ID_UNCONNECTED_PING:
            case ID_UNCONNECTED_PING_OPEN_CONNECTIONS: {
                const bool allowUnconnectedPings = true;
                if (!allowUnconnectedPings)
                    continue;

                // MAGIC (Bedrock specific 8-byte magic number)
                static const uint8_t MAGIC[16] = {
                    0x00, 0xff, 0xff, 0x00,
                    0xfe, 0xfe, 0xfe, 0xfe,
                    0xfd, 0xfd, 0xfd, 0xfd,
                    0x12, 0x34, 0x56, 0x78
                };

                RakNet::BitStream bsIn(packet->data, packet->length, false);
                bsIn.IgnoreBytes(1);  // Skip packet ID

                // Time (echo client's ping timestamp)
                RakNet::Time sendPingTime;
                bsIn.Read(sendPingTime);
                bsIn.Read(MAGIC);

                // Response
                RakNet::BitStream response;
                response.Write(static_cast<RakNet::MessageID>(ID_UNCONNECTED_PONG));
                response.Write(sendPingTime);
                response.Write(this->m_Guid.g); // Server GUID
                response.WriteAlignedBytes(MAGIC, sizeof(MAGIC));

                // MOTD and server data (Bedrock LAN format)
                const std::string& message = this->m_UnconnectedPong;
                if (message.empty())
                    continue;

                response.Write(message.c_str(), static_cast<unsigned int>(message.size()));

                // Send back
                this->m_pPeerInterface->Send(
                    &response,
                    IMMEDIATE_PRIORITY, UNRELIABLE_SEQUENCED,
                    0, packet->systemAddress, false
                );
                break;
            };*/

            // Unhandled Packet
            default:
                break;
        };

        this->m_pPeerInterface->DeallocatePacket(packet);
    };
};

void RakNetServer::sendPacket(BinaryStream& stream, const NetworkPeer::Reliability reliability)
{
    for (const auto &identifier: this->m_Network->getPlayers() | std::views::keys)
    {
        this->sendPacket(identifier, stream, reliability);
    };
};
void RakNetServer::sendPacket(const NetworkIdentifier& identifier, BinaryStream& stream, NetworkPeer::Reliability reliability)
{
    RakNet::BitStream bitStream;
    bitStream.Reset();
    bitStream.WriteAlignedBytes(stream.data(), stream.size());

    RakNet::RakPeerInterface* peerInterface = this->m_pPeerInterface;
    if (peerInterface->GetConnectionState(identifier.m_Guid) != RakNet::ConnectionState::IS_CONNECTED)
        return;

    peerInterface->Send(
        &bitStream,
        PacketPriority::HIGH_PRIORITY, static_cast<PacketReliability>(reliability),
        0, identifier.m_Guid, false
    );
};