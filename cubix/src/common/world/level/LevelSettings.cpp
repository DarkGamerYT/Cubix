#include "LevelSettings.hpp"
LevelSettings::LevelSettings() {
    this->mGameRules.initialize();
};

void LevelSettings::readNetwork(BinaryStream& stream) {

};

void LevelSettings::writeNetwork(BinaryStream& stream) {
    stream.writeUnsignedLong(this->mSeed.getSeed());

    // Spawn settings
    stream.writeShort(static_cast<short>(this->mSpawnSettings.type));
    stream.writeString<Endianness::NetworkEndian>(this->mSpawnSettings.userDefinedBiomeName);
    stream.writeSignedVarInt(this->mSpawnSettings.dimension);

    stream.writeSignedVarInt(static_cast<int>(this->mGeneratorType));
    stream.writeSignedVarInt(static_cast<int>(this->mGameType));
    stream.writeBoolean(this->mIsHardcode);
    stream.writeSignedVarInt(static_cast<int>(this->mDifficulty));
    stream.writeNetworkBlockPosition(this->mDefaultSpawn);
    stream.writeBoolean(this->mAchievementsDisabled);

    // Editor
    stream.writeSignedVarInt(static_cast<int>(this->mEditorWorldType));
    stream.writeBoolean(this->mIsCreatedInEditor);
    stream.writeBoolean(this->mIsExportedFromEditor);

    stream.writeSignedVarInt(this->mTime);
    stream.writeSignedVarInt(this->mEducationEditionOffer);
    stream.writeBoolean(this->mEducationFeaturesEnabled);
    stream.writeString<Endianness::NetworkEndian>(this->mEducationProductID);
    stream.writeUnsignedInt(static_cast<uint32_t>(this->mRainLevel));
    stream.writeUnsignedInt(static_cast<uint32_t>(this->mLightningLevel));

    stream.writeBoolean(this->mPlatformLockedContent);
    stream.writeBoolean(this->mMultiplayerGameIntent);
    stream.writeBoolean(this->mLANBroadcastIntent);
    stream.writeSignedVarInt(static_cast<int>(this->mXBLBroadcastIntent));
    stream.writeSignedVarInt(static_cast<int>(this->mPlatformBroadcastIntent));

    stream.writeBoolean(this->mCommandsEnabled);
    stream.writeBoolean(this->mTexturePacksRequired);

    // GameRules
    const auto& gameRules = this->mGameRules.getRules();

    stream.writeUnsignedVarInt(static_cast<uint32_t>(gameRules.size()));
    for (const GameRule& rule : gameRules)
    {
        stream.writeString<Endianness::NetworkEndian>(rule.getName());
        stream.writeBoolean(rule.canBeModifiedByPlayer());

        GameRuleType ruleType = rule.getType();
        stream.writeUnsignedVarInt(static_cast<uint32_t>(ruleType));

        switch (ruleType)
        {
            case GameRuleType::Boolean:
                stream.writeBoolean(rule.getValue<bool>()); break;
            case GameRuleType::Integer:
                stream.writeUnsignedVarInt(rule.getValue<int>()); break;
            case GameRuleType::Float:
                stream.writeUnsignedInt(static_cast<uint32_t>(rule.getValue<float>())); break;
            default:
                break;
        };
    };

    // Experiments
    stream.writeUnsignedInt(static_cast<uint32_t>(this->getExperiments().size()));
    for (const auto& [ name, isEnabled ] : this->getExperiments())
    {
        stream.writeString<Endianness::NetworkEndian>(name);
        stream.writeBoolean(isEnabled);
    };
    stream.writeBoolean(this->hasHadExperiments());

    stream.writeBoolean(this->mBonusChestEnabled);
    stream.writeBoolean(this->mStartWithMapEnabled);
    stream.writeSignedVarInt(static_cast<int>(this->mDefaultPermissions));
    stream.writeInt(this->mServerChunkTickRange);
    stream.writeBoolean(this->mHasLockedBehaviorPack);
    stream.writeBoolean(this->mHasLockedResourcePack);
    stream.writeBoolean(this->mIsFromLockedTemplate);
    stream.writeBoolean(this->mUseMsaGamertagsOnly);
    stream.writeBoolean(this->mIsFromWorldTemplate);
    stream.writeBoolean(this->mIsWorldTemplateOptionLocked);
    stream.writeBoolean(this->mSpawnV1Villagers);
    stream.writeBoolean(this->mPersonaDisabled);
    stream.writeBoolean(this->mCustomSkinsDisabled);
    stream.writeBoolean(this->mEmoteChatMuted);
    stream.writeString<Endianness::NetworkEndian>(this->mBaseGameVersion.asString());
    stream.writeInt(this->mLimitedWorldWidth);
    stream.writeInt(this->mLimitedWorldDepth);
    stream.writeBoolean(this->mIsNewNether);
    stream.writeString<Endianness::NetworkEndian>(""); // mEduSharedUriResource: Button name
    stream.writeString<Endianness::NetworkEndian>(""); // mEduSharedUriResource: Link uri
    stream.writeBoolean(this->mOverrideForceExperimentalGameplay);
    stream.writeByte(static_cast<uint8_t>(this->mChatRestrictionLevel));
    stream.writeBoolean(this->mDisablePlayerInteractions);

    stream.writeString<Endianness::NetworkEndian>(this->mServerId);
    stream.writeString<Endianness::NetworkEndian>(this->mWorldId);
    stream.writeString<Endianness::NetworkEndian>(this->mScenarioId);
    stream.writeString<Endianness::NetworkEndian>(this->mOwnerId);
};