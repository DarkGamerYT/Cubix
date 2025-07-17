#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SerializedSkin.hpp"
#include "../../../SubClientId.hpp"
#include "../../../network/NetworkPeer.hpp"
#include "../../../network/ConnectionRequest.hpp"
#include "../../../network/packets/ContainerOpenPacket.hpp"
#include "../../../network/packets/DisconnectPacket.hpp"

class ServerNetworkHandler;
class Player {
private:
    ServerNetworkHandler* m_NetworkHandler;
    std::shared_ptr<NetworkPeer> m_NetworkPeer;
    std::unique_ptr<ConnectionRequest> m_Connection;
    SubClientId m_SubClientId;

    std::string m_DisplayName = "Steve";
    SerializedSkin m_Skin{};

public:
    Player(
        std::shared_ptr<NetworkPeer> networkPeer, ServerNetworkHandler* networkHandler,
        std::unique_ptr<ConnectionRequest>& connection, SubClientId subClientId);

    std::unique_ptr<ConnectionRequest>& getConnection() { return m_Connection; };

    const std::string& getDisplayName() { return m_DisplayName; };

    SerializedSkin& getSkin() { return m_Skin; };
    void updateSkin(SerializedSkin& skin);

    void openInventory();
    void doInitialSpawn();

    void disconnect(DisconnectReason, bool skipMessage = false, const std::string& = "disconnectionScreen.noReason") const;
    void sendNetworkPacket(Packet&, NetworkPeer::Reliability = NetworkPeer::Reliability::ReliableOrdered) const;
};

#endif //PLAYER_HPP