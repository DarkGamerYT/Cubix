#pragma once
#include "../Packet.hpp"

#include "./types/Experiments.hpp"
#include "../../world/phys/Vec3.hpp"
#include "../../world/phys/Vec2.hpp"
#include "../../world/level/BlockPos.hpp"
//#include "../../world/level/storage/GameRules.hpp"
#include "../../registry/BlockRegistry.hpp"
#include "../../server/commands/CommandPermissionLevel.hpp"

#include "../../nbt/CompoundTag.hpp"
#include "../../nbt/NbtIo.hpp"
#include "../../world/GameMode.hpp"

enum class Difficulty;

enum class GeneratorType
{
    Legacy = 0,
    Overworld = 1,
    Flat = 2,
    Nether = 3,
    TheEnd = 4,
    Void = 5,
    Undefined = 6
};

struct SpawnSettings
{
    short type;
    std::string userDefinedBiomeName;
    int dimension;
};
struct EduSharedUriResource
{
    std::string buttonName;
    std::string linkUri;
};
struct StartLevelSettings
{
    uint64_t seed;
    SpawnSettings spawnSettings;
    GeneratorType generatorType;
    GameType gameType;
    bool isHardcode;
    Difficulty difficulty;
    BlockPos defaultSpawnBlock;
    bool achievementsDisabled;
    int editorWorldType;
    bool isCreatedInEditor;
    bool isExportedFromEditor;
    int dayCycleStopTime;
    int educationEditionOffer;
    bool educationFeatures;
    std::string educationProductId;
    float rainLevel;
    float lightningLevel;
    bool platformLockedContent;
    bool multiplayerEnabled;
    bool lanBroadcasting;
    int xboxBroadcastSettings;
    int platformBroadcastSettings;
    bool commandsEnabled;
    bool texturepacksRequired;
    //std::vector<std::shared_ptr<GameRule>> gameRules;
    Experiments experiments;
    bool bonusChestEnabled;
    bool startWithMap;
    CommandPermissionLevel playerPermissions;
    int serverTickRange;
    bool hasLockedBehaviorPack;
    bool hasLockedResourcePack;
    bool isFromLockedTemplate;
    bool msaGamertagsOnly;
    bool createdFromTemplate;
    bool isTemplateWithLockedSettings;
    bool onlySpawnV1Villagers;
    bool personaDisabled;
    bool customSkinsDisabled;
    bool emoteChatMuted;
    std::string baseGameVersion;
    int limitedWorldWidth;
    int limitedWorldDepth;
    bool newNether;
    EduSharedUriResource eduSharedUriResource;
    bool overrideForceExperimentalGameplay;
    uint8_t chatRestrictionLevel;
    bool disablePlayerInteractions;

    std::string serverId;
    std::string worldId;
    std::string scenarioId;
};

struct SyncedPlayerMovementSettings
{
    int authorityMode;
    int rewindHistorySize;
    bool serverAuthoratativeBlockBreaking;
};

struct NetworkPermissions
{
    bool serverAuthSoundEnabled;
};

class StartGamePacket : public Packet
{
public:
    int64_t targetActorId;
    int64_t targetRuntimeId;
    GameType actorGameType;
    Vec3 position;
    Vec2 rotation;
    StartLevelSettings settings;
    std::string levelId;
    std::string levelName;
    std::string templateContentIdentity;
    bool isTrial;
    SyncedPlayerMovementSettings movementSettings;
    uint64_t currentLevelTime;
    int enchantmentSeed;
    std::string multiplayerCorrelationId;
    bool enableItemStackNetManager;
    std::string serverVersion;
    Nbt::CompoundTag playerPropertyData;
    uint64_t serverBlockTypeRegistryChecksum;
    Util::UUID worldTemplateId;
    bool clientSideGeneration;
    bool blockNetworkIdsAreHashes;
    NetworkPermissions networkPermissions;

public:
    StartGamePacket()
        : Packet("StartGamePacket", MinecraftPacketIds::StartGame) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};