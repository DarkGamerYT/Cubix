#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SerializedSkin.hpp"

#include "../Actor.hpp"
#include "../../level/Level.hpp"

#include "../../../SubClientId.hpp"
#include "../../../network/peer/NetworkPeer.hpp"
#include "../../../network/connection/ConnectionRequest.hpp"
#include "../../../network/packets/ContainerOpenPacket.hpp"
#include "../../../network/packets/DisconnectPacket.hpp"

class ServerNetworkHandler;
class ServerPlayer;
class Player : public Actor {
    friend class ServerPlayer;

private:
    SubClientId mSubClientId;

    std::string mDisplayName = "Steve";
    SerializedSkin mSkin{};
    std::shared_ptr<Level> mLevel;

    bool mIsLoading = true;
    bool mIsInitialSpawnDone = false;
    uint32_t mLoadingScreenId;

public:
    Player(const std::shared_ptr<Level>& level, SubClientId subClientId);

    const std::string& getDisplayName() { return mDisplayName; };
    void setName(const std::string& name) { this->mDisplayName = name; };

    bool isLoading() const { return this->mIsLoading; };
    virtual bool isPlayerInitialized() const { return this->mIsInitialSpawnDone && !this->isLoading(); };

    SerializedSkin& getSkin() { return mSkin; };
    void updateSkin(SerializedSkin& skin);

    void openInventory() const;

    void move(const Vec3& position) override;
    void tick() override;

    //uint16_t getMaxRenderDistance() const { return this->mConnection->getMaxRenderDistance(); };

    virtual void sendNetworkPacket(Packet&) const {};
};

#endif //PLAYER_HPP