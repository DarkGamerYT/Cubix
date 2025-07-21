#include "Actor.hpp"
void Actor::move(const Vec3& position) {
    this->m_velocity = position - this->m_position;
    this->m_position = position;
};

void Actor::moveTo(const Vec3& position, const Vec2& rotation) {
    this->move(position);
    this->m_rotation = rotation;
};