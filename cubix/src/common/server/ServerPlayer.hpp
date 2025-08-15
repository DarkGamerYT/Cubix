#ifndef SERVERPLAYER_HPP
#define SERVERPLAYER_HPP

#include "../world/actor/player/Player.hpp"

class ServerPlayer : public Player {
private:
    ServerNetworkHandler* mNetworkHandler;
    std::shared_ptr<NetworkPeer> mNetworkPeer;
    std::unique_ptr<ConnectionRequest> mConnection;

    bool mIsPlayerInitialized = false;

public:
    ServerPlayer(
        const std::shared_ptr<Level>& level,
        const std::shared_ptr<NetworkPeer>& networkPeer, ServerNetworkHandler* networkHandler,
        std::unique_ptr<ConnectionRequest>& connection, SubClientId subClientId);

    std::unique_ptr<ConnectionRequest>& getConnection() { return this->mConnection; };

    void markPlayerAsInitialized() { this->mIsPlayerInitialized = true; };
    bool isPlayerInitialized() const override {
        return Player::isPlayerInitialized() && this->mIsPlayerInitialized;
    };
    void doInitialSpawn();

    void tick() override;

    void disconnect(DisconnectReason, bool skipMessage = false, const std::string& = "disconnectionScreen.noReason") const;

    void sendNetworkPacket(Packet&) const override;

    /*template <typename... Args>
    requires (IsNetworkPacket<Args> && ...)
    void sendNetworkPacket(Args& ...args) const {
        this->mNetworkPeer->sendPacket(this->mSubClientId, args...);
    };*/
};

#endif //SERVERPLAYER_HPP
