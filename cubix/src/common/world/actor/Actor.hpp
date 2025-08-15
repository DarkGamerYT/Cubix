#ifndef ACTOR_HPP
#define ACTOR_HPP

#include "../level/ChunkPos.hpp"
#include "../phys/Vec3.hpp"
#include "../phys/Vec2.hpp"

#include "ActorType.hpp"
#include "ActorRuntimeId.hpp"
#include "ActorUniqueId.hpp"

class Actor {
private:
    ActorRuntimeId mRuntimeId;
    ActorUniqueId mUniqueId;

    Vec3 mPosition;
    Vec2 mRotation;
    Vec3 mVelocity;

public:
    Actor() = default;
    virtual ~Actor() = default;

    virtual ActorType getType() const { return ActorType::Undefined; };

    const ActorRuntimeId& getRuntimeId() const { return this->mRuntimeId; };
    void setRuntimeId(const ActorRuntimeId& id) { this->mRuntimeId = id; };

    const ActorUniqueId& getUniqueId() const { return this->mUniqueId; };
    void setUniqueId(const ActorUniqueId& id);

    const Vec3& getPosition() const { return this->mPosition; };
    const Vec3& getVelocity() const { return this->mVelocity; };
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
