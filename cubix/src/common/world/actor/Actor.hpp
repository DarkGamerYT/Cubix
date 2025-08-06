#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "../level/ChunkPos.hpp"
#include "../phys/Vec3.hpp"
#include "../phys/Vec2.hpp"

class Actor {
private:
    Vec3 mPosition;
    Vec2 mRotation;
    Vec3 mVelocity;

public:
    Actor() = default;
    virtual ~Actor() = default;

    const Vec3& getPosition() const { return this->mPosition; };
    ChunkPos getChunkPos() const {
        return {
            static_cast<int>(this->mPosition.x) >> 4,
            static_cast<int>(this->mPosition.z) >> 4
        };
    };

    virtual void move(const Vec3& position);
    void moveTo(const Vec3& position, const Vec2& rotation);

    virtual void tick() = 0;
};

#endif //ACTOR_HPP
