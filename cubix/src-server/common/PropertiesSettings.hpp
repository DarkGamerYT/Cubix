#ifndef PROPERTIES_SETTINGS_HPP
#define PROPERTIES_SETTINGS_HPP

#include <algorithm>
#include <functional>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string_view>

#include "../../src/common/network/CompressionType.hpp"
#include "../../src/common/network/TransportLayer.hpp"
#include "../../src/common/server/ChatRestrictionLevel.hpp"
#include "../../src/common/world/GameMode.hpp"
#include "../../src/common/world/Difficulty.hpp"
#include "../../src/common/server/PlayerTickPolicy.hpp"
#include "../../src/common/server/commands/types/PlayerPermissionLevel.hpp"
#include "../../src/common/server/commands/types/CommandPermissionLevel.hpp"
#include "../../src/common/util/StringUtils.hpp"

class PropertiesSettings
{
private:
    bool mIsLoaded;
    std::unordered_map<std::string, std::string> mCustomProperties;

    GameType mGameMode = GameType::Survival;
    Difficulty mDifficulty = Difficulty::Normal;
    std::string mServerName = "Dedicated Server";
    int mMaxPlayers = 10;
    CommandPermissionLevel mOpPermissionLevel = CommandPermissionLevel::GameDirectors;
    unsigned short mServerPort = 19132;
    unsigned short mServerPortV6 = 19133;
    std::string mLevelName = "level";
    std::string mLevelSeed;
    bool mForceGameMode = false;
    bool mAllowCheats = false;
    int mTickDistance = 64 >> 4;
    PlayerPermissionLevel mDefaultPermissionLevel = PlayerPermissionLevel::Member;
    PlayerTickPolicy mPlayerTickPolicy = PlayerTickPolicy::THROTTLED;
    ChatRestrictionLevel mChatRestrictionLevel = ChatRestrictionLevel::None;
    CompressionType mCompressionAlgorithm = CompressionType::Zlib;
    short mCompressionThreshold = 0;
    TransportLayer mTransportLayer = TransportLayer::Default;
    bool mOnlineMode = true;
    bool mAllowList = false;
    bool mIsVisibleToLan = true;

public:
    explicit PropertiesSettings(const std::string& name);

    bool isPropertiesFileLoaded() const { return this->mIsLoaded; };
    const std::string& getCustomProperty(const std::string& name) { return this->mCustomProperties[name]; };

    static bool parseBoolean(const std::string& buffer) { return buffer == "true"; };
    static int parseInt(const std::string& buffer) { return std::strtol(buffer.c_str(), 0, 0); };

    GameType getGameMode() const { return this->mGameMode; };
    Difficulty getDifficulty() const { return this->mDifficulty; };
    const std::string& getServerName() const { return this->mServerName; };
    int getMaxPlayers() const { return this->mMaxPlayers; };
    CommandPermissionLevel getOpPermissionLevel() const { return this->mOpPermissionLevel; };
    unsigned short getServerPort() const { return this->mServerPort; };
    unsigned short getServerPortV6() const { return this->mServerPortV6; };
    const std::string& getLevelName() const { return this->mLevelName; };
    const std::string& getLevelSeed() const { return this->mLevelSeed; };
    bool forceGameMode() const { return this->mForceGameMode; };
    bool allowCheats() const { return this->mAllowCheats; };
    bool getServerTickRange() const { return this->mTickDistance; };
    PlayerTickPolicy getPlayerTickPolicy() const { return this->mPlayerTickPolicy; };
    PlayerPermissionLevel getDefaultPermissionLevel() const { return this->mDefaultPermissionLevel; };
    ChatRestrictionLevel getChatRestrictionLevel() const { return this->mChatRestrictionLevel; };
    CompressionType getCompressionAlgorithm() const { return this->mCompressionAlgorithm; };
    short getCompressionThreshold() const { return this->mCompressionThreshold; };
    TransportLayer getTransportLayer() const { return this->mTransportLayer; };
    bool useAllowList() const { return this->mAllowList; };
    bool useOnlineAuthentication() const { return this->mOnlineMode; };
    bool isServerVisibleToLanDiscovery() const { return this->mIsVisibleToLan; };
};

#endif // !PROPERTIES_SETTINGS_HPP
