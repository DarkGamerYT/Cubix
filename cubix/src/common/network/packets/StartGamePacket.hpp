#pragma once
#include "../Packet.hpp"

#include "../../world/phys/Vec3.hpp"
#include "../../world/phys/Vec2.hpp"
#include "../../world/level/BlockPos.hpp"
#include "../../world/level/storage/Experiments.hpp"
//#include "../../world/level/storage/GameRules.hpp"
#include "../../registry/BlockRegistry.hpp"
#include "../../server/commands/types/CommandPermissionLevel.hpp"

#include "../../nbt/CompoundTag.hpp"
#include "../../nbt/NbtIo.hpp"
#include "../../world/GameMode.hpp"
#include "../../world/level/LevelSettings.hpp"

struct SyncedPlayerMovementSettings
{
    int rewindHistorySize;
    bool serverAuthoratativeBlockBreaking;
};

struct NetworkPermissions
{
    bool serverAuthSoundEnabled;
};

class StartGamePacket final : public Packet
{
public:
    int64_t targetActorId;
    int64_t targetRuntimeId;
    GameType actorGameType;
    Vec3 position;
    Vec2 rotation;
    std::shared_ptr<LevelSettings> levelSettings;
    std::string levelId;
    std::string levelName;
    Util::UUID templateContentIdentity;
    bool isTrial;
    SyncedPlayerMovementSettings movementSettings;
    uint64_t tick;
    int enchantmentSeed;
    std::string multiplayerCorrelationId;
    bool enableItemStackNetManager;
    std::string serverVersion;
    Nbt::CompoundTag playerPropertyData;
    uint64_t serverBlockTypeRegistryChecksum;
    Util::UUID worldTemplateId;
    bool clientSideGeneration;
    bool blockNetworkIdsAreHashes;
    bool tickDeathSystemsEnabled;
    NetworkPermissions networkPermissions;

public:
    StartGamePacket()
        : Packet("StartGamePacket", MinecraftPacketIds::StartGame) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};