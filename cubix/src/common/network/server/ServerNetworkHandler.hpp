#ifndef SERVERNETWORKHANDLER
#define SERVERNETWORKHANDLER

#include <unordered_map>
#include <memory>
#include <sstream>

#include "../../SharedConstants.hpp"
#include "../../SubClientId.hpp"
#include "../../server/ServerPlayer.hpp"
#include "../../server/ServerLevel.hpp"
#include "../../world/GameMode.hpp"
#include "../../world/Difficulty.hpp"
#include "../../world/level/chunk/Chunk.hpp"
#include "../../world/actor/player/Player.hpp"
#include "../../world/actor/player/SerializedSkin.hpp"

#include "../transport/TransportLayer.hpp"
#include "../transport/RakNetServer.hpp"
#include "../transport/NetherNetServer.hpp"
#include "../PacketIds.hpp"
#include "ConnectionDefinition.hpp"

#include "../packets/RequestNetworkSettingsPacket.hpp"
#include "../packets/PlayStatusPacket.hpp"
#include "../packets/DisconnectPacket.hpp"
#include "../packets/NetworkSettingsPacket.hpp"
#include "../packets/LoginPacket.hpp"
#include "../packets/SubClientLoginPacket.hpp"
#include "../packets/ServerToClientHandshakePacket.hpp"
#include "../packets/ClientToServerHandshakePacket.hpp"
#include "../packets/ResourcePacksInfoPacket.hpp"
#include "../packets/ClientCacheStatusPacket.hpp"
#include "../packets/ResourcePackClientResponsePacket.hpp"
#include "../packets/ResourcePackStackPacket.hpp"
#include "../packets/StartGamePacket.hpp"
#include "../packets/SetLocalPlayerAsInitializedPacket.hpp"
#include "../packets/CreativeContentPacket.hpp"
#include "../packets/ItemRegistryPacket.hpp"
#include "../packets/AvailableCommandsPacket.hpp"
#include "../packets/TextPacket.hpp"
#include "../packets/InteractPacket.hpp"
#include "../packets/ContainerOpenPacket.hpp"
#include "../packets/ContainerClosePacket.hpp"
#include "../packets/RequestChunkRadiusPacket.hpp"
#include "../packets/ChunkRadiusUpdatedPacket.hpp"
#include "../packets/LevelChunkPacket.hpp"
#include "../packets/NetworkChunkPublisherUpdatePacket.hpp"
#include "../packets/BlockActorDataPacket.hpp"
#include "../packets/PlayerSkinPacket.hpp"
#include "../packets/CommandRequestPacket.hpp"
#include "../packets/CommandOutputPacket.hpp"
#include "../packets/ServerboundLoadingScreenPacket.hpp"
#include "../packets/PlayerAuthInputPacket.hpp"
#include "../packets/AnimatePacket.hpp"
#include "../packets/PlayerListPacket.hpp"

class ServerInstance;
class ServerNetworkHandler
{
public:
    using Connections = std::unordered_map<NetworkIdentifier, std::shared_ptr<NetworkPeer>>;
    using Players = std::unordered_map<SubClientId, std::shared_ptr<ServerPlayer>>;
    using Clients = std::unordered_map<NetworkIdentifier, Players>;

private:
    TransportLayer mTransportLayer = TransportLayer::Default;
    Connections mConnections;
    Clients mPlayers;
    ConnectionDefinition mConnectionDefinition;
    bool mRequireOnlineAuthentication;

    std::unique_ptr<NetworkServer> mNetworkServer;
    ServerInstance* mServerInstance;
    std::shared_ptr<ServerLevel> mLevel;

public:
    ServerNetworkHandler(
        const std::shared_ptr<ServerLevel>&,
        ServerInstance*,
        const ConnectionDefinition&,
        bool requireOnlineAuthentication);
    ~ServerNetworkHandler();

    void initializeNetwork();
    void onTick(uint32_t nTick);
    void onTickPlayers(uint32_t nTick);
    void shutdown();

    void setTransportLayer(const TransportLayer layer) { this->mTransportLayer = layer; };
    TransportLayer getTransportLayer() const { return this->mTransportLayer; };

    std::vector<std::shared_ptr<NetworkPeer>> getConnections() const;
    std::vector<std::shared_ptr<ServerPlayer>> getPlayers() const;

    /*NetworkIdentifier getNetworkIdentifier(const std::string& xuid) {
        const auto it = std::ranges::find_if(
            this->m_Players,
            [&](const auto& pair) {
                const auto& player = pair.second;
                return player && player->getConnection()->getXuid() == xuid;
            });

        if (it != this->m_Players.end())
            return it->first;

        return {};
    };*/

    void onConnect(NetworkIdentifier&);
    void onDisconnect(const NetworkIdentifier&);
    void disconnectClient(const NetworkIdentifier&, SubClientId, DisconnectReason, bool skipMessage = true, const std::string & = "");
    void sendPacket(Packet& packet) const;
    void handle(NetworkIdentifier&, BinaryStream&);

    void handle(NetworkIdentifier&, RequestNetworkSettingsPacket&);
    void handle(NetworkIdentifier&, LoginPacket&);
    void handle(NetworkIdentifier&, SubClientLoginPacket&);
    void handle(NetworkIdentifier&, ClientToServerHandshakePacket&);
    void handle(NetworkIdentifier&, ClientCacheStatusPacket&);
    void handle(NetworkIdentifier&, ResourcePackClientResponsePacket&);
    void handle(NetworkIdentifier&, SetLocalPlayerAsInitializedPacket&);
    void handle(NetworkIdentifier&, InteractPacket&);
    void handle(NetworkIdentifier&, TextPacket&);
    void handle(NetworkIdentifier&, ContainerClosePacket&);
    void handle(NetworkIdentifier&, RequestChunkRadiusPacket&);
    void handle(NetworkIdentifier&, PlayerSkinPacket&);
    void handle(NetworkIdentifier&, CommandRequestPacket&);
    void handle(NetworkIdentifier&, PlayerAuthInputPacket&);
    void handle(NetworkIdentifier&, AnimatePacket&);

private:
    std::shared_ptr<ServerPlayer> createNewPlayer(const NetworkIdentifier&, SubClientId, std::unique_ptr<ConnectionRequest>&);

    std::shared_ptr<ServerPlayer> getServerPlayer(const NetworkIdentifier&, SubClientId);
    std::shared_ptr<ServerPlayer> getPlayer(const NetworkIdentifier&, SubClientId, const ActorUniqueId&);
    std::shared_ptr<ServerPlayer> getPlayer(const NetworkIdentifier&, SubClientId, const ActorRuntimeId&);
};

#endif // !SERVERNETWORKHANDLER
