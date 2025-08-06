#include "RakNetServer.hpp"
#include "ServerNetworkHandler.hpp"
RakNetServer::RakNetServer(ServerNetworkHandler* networkHandler)
{
    this->p_mPeerInterface = RakNet::RakPeerInterface::GetInstance();
    this->mGuid = this->p_mPeerInterface->GetMyGUID();

    this->mNetwork = networkHandler;
    this->mIdentifier = NetworkIdentifier(this->mGuid);
};

void RakNetServer::startServer(PortPair ports, int maxPlayers)
{
    constexpr int socketCount = RAKNET_SUPPORT_IPV6 ? 2 : 1;
    this->mSocketDescriptor[0].socketFamily = AF_INET;
    this->mSocketDescriptor[0].port = ports.mPortV4;
#if RAKNET_SUPPORT_IPV6
    this->mSocketDescriptor[1].socketFamily = AF_INET6;
    this->mSocketDescriptor[1].port = ports.mPortV6;
#endif

    switch (this->p_mPeerInterface->Startup(maxPlayers, this->mSocketDescriptor, socketCount))
    {
        case RakNet::RAKNET_STARTED: {
            this->p_mPeerInterface->SetMaximumIncomingConnections(maxPlayers);

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
                    pServerLocator->p_mPeerInterface != nullptr
                    && pServerLocator->p_mPeerInterface->IsActive()
                ) {
                    const std::string& message = pServerLocator->mUnconnectedPong;
                    if (!message.empty())
                    {
                        pServerLocator->p_mPeerInterface->SetOfflinePingResponse(message.c_str(), message.size());
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

            this->mNetwork->shutdown();
            break;
        };
        default: {
            break;
        };
    };
};

void RakNetServer::stopServer()
{
    std::lock_guard<std::mutex> lock(this->mPeerMutex);
    if (this->p_mPeerInterface != nullptr)
    {
        {
            // Drain packets
            RakNet::Packet* packet = nullptr;
            while ((packet = this->p_mPeerInterface->Receive()) != nullptr)
                this->p_mPeerInterface->DeallocatePacket(packet);
        };

        this->p_mPeerInterface->Shutdown(1);
        RakNet::RakPeerInterface::DestroyInstance(this->p_mPeerInterface);
        this->p_mPeerInterface = nullptr;
    };
};

void RakNetServer::disconnectClient(
    const NetworkIdentifier& networkIdentifier,
    const SubClientId subClientId,
    const DisconnectReason disconnectReason,
    const bool skipMessage,
    const std::string& message
) {
    this->mNetwork->disconnectClient(
        networkIdentifier, subClientId,
        disconnectReason, skipMessage, message);
    this->p_mPeerInterface->CloseConnection(networkIdentifier.mGuid, true);
};

void RakNetServer::update()
{
    std::lock_guard<std::mutex> lock(this->mPeerMutex);
    if (this->p_mPeerInterface == nullptr)
        return;

    RakNet::Packet* packet = nullptr;
    while ((packet = this->p_mPeerInterface->Receive()) != nullptr)
    {
        const uint8_t packetId = packet->data[0];
        NetworkIdentifier networkIdentifier(packet->guid);
        switch (packetId)
        {
            // Minecraft Packets
            case 0xFE:
            {
                if (this->p_mPeerInterface->GetConnectionState(networkIdentifier.mGuid) != RakNet::ConnectionState::IS_CONNECTED)
                    return;

                const auto& connections = this->mNetwork->getConnections();
                auto it = std::ranges::find_if(connections, [networkIdentifier](const auto& identifier) {
                    return identifier->getNetworkIdentifier() == networkIdentifier;
                });

                if (it == connections.end())
                    continue;

                const size_t index = std::distance(connections.begin(), it);
                const std::shared_ptr<NetworkPeer>& networkPeer = connections.at(index);

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

                        const uint8_t* buffer = stream.readBytes(payloadSize);
                        std::vector payload(buffer, buffer + payloadSize);

                        BinaryStream packetStream(payload);
                        this->mNetwork->handle(networkIdentifier, packetStream);
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
                this->mNetwork->onConnect(networkIdentifier);

                Logger::log(Logger::LogLevel::Debug,
                    "Incoming connection. ServerID: raknet:{}, ClientID: raknet:{}", this->mGuid.g, packet->guid.g);
                break;
            };

            case ID_CONNECTION_LOST:
            case ID_CONNECTION_ATTEMPT_FAILED:
            case ID_DISCONNECTION_NOTIFICATION:
            {
                this->mNetwork->onDisconnect(networkIdentifier);
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
                response.Write(this->mGuid.g); // Server GUID
                response.WriteAlignedBytes(MAGIC, sizeof(MAGIC));

                // MOTD and server data (Bedrock LAN format)
                const std::string& message = this->mUnconnectedPong;
                if (message.empty())
                    continue;

                response.Write(message.c_str(), message.size());

                // Send back
                this->p_mPeerInterface->Send(
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

        this->p_mPeerInterface->DeallocatePacket(packet);
    };
};

void RakNetServer::sendPacket(BinaryStream& stream, const NetworkPeer::Reliability reliability)
{
    for (const auto &networkPeer: this->mNetwork->getConnections())
    {
        this->sendPacket(networkPeer->getNetworkIdentifier(), stream, reliability);
    };
};
void RakNetServer::sendPacket(const NetworkIdentifier& identifier, BinaryStream& stream, NetworkPeer::Reliability reliability)
{
    RakNet::BitStream bitStream;
    bitStream.Reset();
    bitStream.WriteAlignedBytes(stream.data(), stream.size());

    RakNet::RakPeerInterface* peerInterface = this->p_mPeerInterface;
    if (peerInterface == nullptr
        || peerInterface->GetConnectionState(identifier.mGuid) != RakNet::ConnectionState::IS_CONNECTED)
        return;

    peerInterface->Send(
        &bitStream,
        PacketPriority::HIGH_PRIORITY, static_cast<PacketReliability>(reliability),
        0, identifier.mGuid, false
    );
};