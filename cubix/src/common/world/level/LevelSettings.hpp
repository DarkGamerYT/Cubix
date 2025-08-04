#ifndef LEVESETTINGS_HPP
#define LEVESETTINGS_HPP

#include <cstdint>
#include <string>

#include "../../util/BinaryStream.hpp"

#include "../../editor/WorldType.hpp"
#include "../../network/GamePublishSetting.hpp"
#include "../../server/ChatRestrictionLevel.hpp"
#include "../../server/commands/CommandPermissionLevel.hpp"

#include "../Difficulty.hpp"
#include "../GameMode.hpp"
#include "SpawnBiomeType.hpp"
#include "levelgen/GeneratorType.hpp"
#include "storage/Experiments.hpp"
#include "storage/GameRules.hpp"
#include "storage/LevelSeed64.hpp"

struct SpawnSettings {
    SpawnBiomeType type = SpawnBiomeType::Default;
    std::string userDefinedBiomeName = "plains";
    int dimension = 0;
};

class LevelSettings {
private:
    LevelSeed64 mSeed{ 0 };
    GameType mGameType = GameType::Survival;
    bool mIsHardcode = false;
    Difficulty mDifficulty = Difficulty::Easy;
    BlockPos mDefaultSpawn;
    bool mIsNewNether = true;

    // Editor
    Editor::WorldType mEditorWorldType = Editor::WorldType::NonEditor;
    bool mIsCreatedInEditor = false;
    bool mIsExportedFromEditor = false;

    bool mPlatformLockedContent = false;
    bool mMultiplayerGameIntent = true;
    bool mLANBroadcastIntent = true;
    GamePublishSetting mXBLBroadcastIntent = GamePublishSetting::Public;
    GamePublishSetting mPlatformBroadcastIntent = GamePublishSetting::Public;

    float mRainLevel = 0;
    float mLightningLevel = 0;
    int mTime = 0;
    bool mAchievementsDisabled = false;
    bool mDisablePlayerInteractions = false;
    bool mCheatsEnabled = false;
    bool mAdventureModeOverridesEnabled = false;
    bool mCommandsEnabled = false;
    bool mTexturePacksRequired = false;
    bool mHasLockedBehaviorPack = false;
    bool mHasLockedResourcePack = false;
    bool mIsRandomSeedAllowed = true;
    bool mUseMsaGamertagsOnly = false;
    bool mOverrideSettings = false;
    bool mBonusChestEnabled = false;
    bool mStartWithMapEnabled = false;
    // 4 chunks (64x64 blocks), 6 chunks (96x96 blocks), 8 chunks (128x128 blocks)
    int mServerChunkTickRange = 64 >> 4;
    bool mIsFromWorldTemplate = false;
    bool mIsFromLockedTemplate = false;
    bool mIsWorldTemplateOptionLocked = false;
    bool mSpawnV1Villagers = false;
    bool mPersonaDisabled = false;
    bool mCustomSkinsDisabled = false;
    bool mEmoteChatMuted = false;

    // Education Edition
    int mEducationEditionOffer = 0;
    bool mEducationFeaturesEnabled = false;
    std::string mEducationProductID;

    int mLimitedWorldWidth = 16;
    int mLimitedWorldDepth = 16;

    ChatRestrictionLevel mChatRestrictionLevel = ChatRestrictionLevel::None;
    CommandPermissionLevel mDefaultPermissions = CommandPermissionLevel::Any;
    GeneratorType mGeneratorType = GeneratorType::Overworld;
    SpawnSettings mSpawnSettings;
    Experiments mExperiments{};
    bool mOverrideForceExperimentalGameplay = false;
    GameRules mGameRules{};
    GameVersion mBaseGameVersion = SharedConstants::CurrentGameVersion;

    std::string mServerId;
    std::string mWorldId;
    std::string mScenarioId;
    std::string mOwnerId;

public:
    LevelSettings();

    GameType getGameType() const { return this->mGameType; };
    Difficulty getDifficulty() const { return this->mDifficulty; };
    const LevelSeed64& getSeed() const { return this->mSeed; };
    ExperimentStorage& getExperiments() { return this->mExperiments.experimentList; };
    bool hasHadExperiments() const { return this->mExperiments.experimentsEverEnabled; };

    void setGameType(const GameType gameType) { this->mGameType = gameType; };
    void setDifficulty(const Difficulty difficulty) { this->mDifficulty = difficulty; };
    void setSeed(const LevelSeed64& seed) { this->mSeed = seed; };
    void setHasHadExperiments(const bool value) { this->mExperiments.experimentsEverEnabled = value; };

    void readNetwork(BinaryStream&);
    void writeNetwork(BinaryStream&);
};

#endif //LEVESETTINGS_HPP
