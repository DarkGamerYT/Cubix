#include "Player.hpp"

#include "../../../network/packets/StartGamePacket.hpp"
#include "../../../network/packets/PlayerListPacket.hpp"

Player::Player(const std::shared_ptr<Level>& level,  const SubClientId subClientId) {
    this->mLevel = level;
    this->mSubClientId = subClientId;
};

void Player::updateSkin(SerializedSkin& skin) {
    this->mSkin = std::move(skin);
};

void Player::move(const Vec3& position) {
    Actor::move(position);

};

void Player::tick() {

};

void Player::openInventory() const {
    ContainerOpenPacket containerOpen;
    containerOpen.actorUniqueId = 0;
    containerOpen.position = BlockPos{ 0.0, 0.0, 0.0 };
    containerOpen.containerId = 0;
    containerOpen.containerType = ContainerType::INVENTORY;

    this->sendNetworkPacket(containerOpen);
};