#include "Actor.hpp"
void Actor::move(const Vec3& position) {
    this->mVelocity = position - this->mPosition;
    this->mPosition = position;
};

void Actor::moveTo(const Vec3& position, const Vec2& rotation) {
    this->move(position);
    this->mRotation = rotation;
};