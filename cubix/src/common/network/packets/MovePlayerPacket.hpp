#pragma once
#include "../Packet.hpp"

#include "../../world/phys/Vec3.hpp"
#include "../../world/phys/Vec2.hpp"
#include "../../world/actor/ActorType.hpp"

enum class PositionMode : uint8_t {
    Normal      = 0,
    Respawn     = 1,
    Teleport    = 2,
    OnlyHeadRot = 3
};

enum class TeleportationCause {
    Unknown     = 0,
    Projectile  = 1,
    ChorusFruit = 2,
    Command     = 3,
    Behavior    = 4
};

class MovePlayerPacket final : public Packet
{
public:
    int64_t actorRuntimeId;
    Vec3 position;
    Vec2 rotation;
    float yHeadRotation;
    PositionMode positionMode;
    bool isOnGround;
    int64_t ridingRuntimeId;
    TeleportationCause teleportCause = TeleportationCause::Unknown;
    ActorType sourceActorType = ActorType::Player;
    uint64_t tick;

public:
    MovePlayerPacket()
        : Packet("MovePlayerPacket", MinecraftPacketIds::MovePlayer) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};