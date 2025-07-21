#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SerializedSkin.hpp"

#include "../Actor.hpp"

#include "../../../SubClientId.hpp"
#include "../../../network/NetworkPeer.hpp"
#include "../../../network/ConnectionRequest.hpp"
#include "../../../network/packets/ContainerOpenPacket.hpp"
#include "../../../network/packets/DisconnectPacket.hpp"

class ServerNetworkHandler;
class Player : public Actor {
private:
    ServerNetworkHandler* m_networkHandler;
    std::shared_ptr<NetworkPeer> m_networkPeer;
    std::unique_ptr<ConnectionRequest> m_connection;
    SubClientId m_subClientId;

    std::string m_displayName = "Steve";
    SerializedSkin m_skin{};

public:
    Player(
        std::shared_ptr<NetworkPeer> networkPeer, ServerNetworkHandler* networkHandler,
        std::unique_ptr<ConnectionRequest>& connection, SubClientId subClientId);

    std::unique_ptr<ConnectionRequest>& getConnection() { return m_connection; };

    const std::string& getDisplayName() { return m_displayName; };

    SerializedSkin& getSkin() { return m_skin; };
    void updateSkin(SerializedSkin& skin);

    void openInventory() const;
    void doInitialSpawn();

    void move(const Vec3& position) override;
    void tick() override;

    unsigned int getMaxRenderDistance() const { return this->m_connection->getMaxRenderDistance(); };

    void disconnect(DisconnectReason, bool skipMessage = false, const std::string& = "disconnectionScreen.noReason") const;


    template <typename... Args>
    requires (IsNetworkPacket<Args> && ...)
    void sendNetworkPacket(Args& ...args) const {
        this->m_networkPeer->sendPacket(this->m_subClientId, args...);
    };
};

#endif //PLAYER_HPP