#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SerializedSkin.hpp"

#include "../Actor.hpp"
#include "../../level/Level.hpp"

#include "../../../SubClientId.hpp"
#include "../../../network/NetworkPeer.hpp"
#include "../../../network/ConnectionRequest.hpp"
#include "../../../network/packets/ContainerOpenPacket.hpp"
#include "../../../network/packets/DisconnectPacket.hpp"

class ServerNetworkHandler;
class Player : public Actor {
private:
    ServerNetworkHandler* mNetworkHandler;
    std::shared_ptr<NetworkPeer> mNetworkPeer;
    std::unique_ptr<ConnectionRequest> mConnection;
    SubClientId mSubClientId;

    std::string mDisplayName = "Steve";
    SerializedSkin mSkin{};
    std::shared_ptr<Level> mLevel;

public:
    Player(
        const std::shared_ptr<Level>& level,
        const std::shared_ptr<NetworkPeer> &networkPeer, ServerNetworkHandler* networkHandler,
        std::unique_ptr<ConnectionRequest>& connection, SubClientId subClientId);

    std::unique_ptr<ConnectionRequest>& getConnection() { return mConnection; };

    const std::string& getDisplayName() { return mDisplayName; };

    SerializedSkin& getSkin() { return mSkin; };
    void updateSkin(SerializedSkin& skin);

    void openInventory() const;
    void doInitialSpawn();

    void move(const Vec3& position) override;
    void tick() override;

    uint16_t getMaxRenderDistance() const { return this->mConnection->getMaxRenderDistance(); };

    void disconnect(DisconnectReason, bool skipMessage = false, const std::string& = "disconnectionScreen.noReason") const;


    template <typename... Args>
    requires (IsNetworkPacket<Args> && ...)
    void sendNetworkPacket(Args& ...args) const {
        this->mNetworkPeer->sendPacket(this->mSubClientId, args...);
    };
};

#endif //PLAYER_HPP