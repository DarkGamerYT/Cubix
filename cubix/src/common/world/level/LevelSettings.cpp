#include "LevelSettings.hpp"
LevelSettings::LevelSettings() {
    this->mGameRules.initialize();
};

LevelSettings BinaryStream::serialize<LevelSettings>::read(BinaryStream& stream) {
    return {};
};

void BinaryStream::serialize<LevelSettings>::write(const LevelSettings& value, BinaryStream& stream) {
    stream.writeUnsignedLong(value.mSeed.getSeed());

    // Spawn settings
    stream.writeShort(static_cast<short>(value.mSpawnSettings.type));
    stream.writeString<Endianness::NetworkEndian>(value.mSpawnSettings.userDefinedBiomeName);
    stream.writeSignedVarInt(value.mSpawnSettings.dimension);

    stream.writeSignedVarInt(static_cast<int>(value.mGeneratorType));
    stream.writeSignedVarInt(static_cast<int>(value.mGameType));
    stream.writeBoolean(value.mIsHardcode);
    stream.writeSignedVarInt(static_cast<int>(value.mDifficulty));
    stream.writeNetworkBlockPosition(value.mDefaultSpawn);
    stream.writeBoolean(value.mAchievementsDisabled);

    // Editor
    stream.writeSignedVarInt(static_cast<int>(value.mEditorWorldType));
    stream.writeBoolean(value.mIsCreatedInEditor);
    stream.writeBoolean(value.mIsExportedFromEditor);

    stream.writeSignedVarInt(value.mTime);
    stream.writeSignedVarInt(value.mEducationEditionOffer);
    stream.writeBoolean(value.mEducationFeaturesEnabled);
    stream.writeString<Endianness::NetworkEndian>(value.mEducationProductID);
    stream.write<float>(value.mRainLevel);
    stream.write<float>(value.mLightningLevel);

    stream.writeBoolean(value.mPlatformLockedContent);
    stream.writeBoolean(value.mMultiplayerGameIntent);
    stream.writeBoolean(value.mLANBroadcastIntent);
    stream.writeSignedVarInt(static_cast<int>(value.mXBLBroadcastIntent));
    stream.writeSignedVarInt(static_cast<int>(value.mPlatformBroadcastIntent));

    stream.writeBoolean(value.mCommandsEnabled);
    stream.writeBoolean(value.mTexturePacksRequired);

    // GameRules
    const auto& gameRules = value.mGameRules.getRules();

    stream.writeUnsignedVarInt(static_cast<uint32_t>(gameRules.size()));
    for (const auto& rule : gameRules)
    {
        stream.writeString<Endianness::NetworkEndian>(rule->getName());
        stream.writeBoolean(rule->canBeModifiedByPlayer());

        GameRuleType ruleType = rule->getType();
        stream.writeUnsignedVarInt(static_cast<uint32_t>(ruleType));

        switch (ruleType)
        {
            case GameRuleType::Boolean: {
                const auto gameRule = dynamic_cast<const GameRule<bool>*>(rule.get());
                stream.writeBoolean(gameRule->getValue());
                break;
            };
            case GameRuleType::Integer: {
                const auto gameRule = dynamic_cast<const GameRule<int>*>(rule.get());
                stream.writeUnsignedVarInt(gameRule->getValue());
                break;
            };
            case GameRuleType::Float: {
                const auto gameRule = dynamic_cast<const GameRule<float>*>(rule.get());
                stream.write<float>(gameRule->getValue());
                break;
            };
            default:
                break;
        };
    };

    // Experiments
    const ExperimentStorage& experiments = value.mExperiments.experimentList;

    stream.writeUnsignedInt(static_cast<uint32_t>(experiments.size()));
    for (const auto& [ name, isEnabled ] : experiments)
    {
        stream.writeString<Endianness::NetworkEndian>(name);
        stream.writeBoolean(isEnabled);
    };
    stream.writeBoolean(value.hasHadExperiments());

    stream.writeBoolean(value.mBonusChestEnabled);
    stream.writeBoolean(value.mStartWithMapEnabled);
    stream.writeSignedVarInt(static_cast<int>(value.mPlayerPermissionLevel));
    stream.writeInt(value.mServerChunkTickRange);
    stream.writeBoolean(value.mHasLockedBehaviorPack);
    stream.writeBoolean(value.mHasLockedResourcePack);
    stream.writeBoolean(value.mIsFromLockedTemplate);
    stream.writeBoolean(value.mUseMsaGamertagsOnly);
    stream.writeBoolean(value.mIsFromWorldTemplate);
    stream.writeBoolean(value.mIsWorldTemplateOptionLocked);
    stream.writeBoolean(value.mSpawnV1Villagers);
    stream.writeBoolean(value.mPersonaDisabled);
    stream.writeBoolean(value.mCustomSkinsDisabled);
    stream.writeBoolean(value.mEmoteChatMuted);
    stream.writeString<Endianness::NetworkEndian>(value.mBaseGameVersion.asString());
    stream.writeInt(value.mLimitedWorldWidth);
    stream.writeInt(value.mLimitedWorldDepth);
    stream.writeBoolean(value.mIsNewNether);
    stream.writeString<Endianness::NetworkEndian>(""); // mEduSharedUriResource: Button name
    stream.writeString<Endianness::NetworkEndian>(""); // mEduSharedUriResource: Link uri
    stream.writeBoolean(value.mOverrideForceExperimentalGameplay);
    stream.writeByte(static_cast<uint8_t>(value.mChatRestrictionLevel));
    stream.writeBoolean(value.mDisablePlayerInteractions);

    stream.writeString<Endianness::NetworkEndian>(value.mServerId);
    stream.writeString<Endianness::NetworkEndian>(value.mWorldId);
    stream.writeString<Endianness::NetworkEndian>(value.mScenarioId);
    stream.writeString<Endianness::NetworkEndian>(value.mOwnerId);
};