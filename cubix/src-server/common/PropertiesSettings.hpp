#ifndef PROPERTIES_SETTINGS_HPP
#define PROPERTIES_SETTINGS_HPP

#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string_view>

#include "../../src/common/world/GameMode.hpp"
#include "../../src/common/world/Difficulty.hpp"
#include "../../src/common/server/PlayerTickPolicy.hpp"

class PropertiesSettings
{
private:
    bool m_IsLoaded;
    std::unordered_map<std::string, std::string> m_CustomProperties;

    std::string m_GameMode;
    std::string m_Difficulty;
    std::string m_ServerName;
    int m_MaxPlayers;
    int m_OpPermissionLevel;
    unsigned short m_ServerPort;
    unsigned short m_ServerPortV6;
    std::string m_LevelName;
    std::string m_LevelSeed;
    bool m_ForceGameMode;
    bool m_AllowCheats;
    int m_TickDistance;
    std::string m_DefaultPermissionLevel;
    std::string m_PlayerTickPolicy;
    int m_ChatRestrictionLevel;
    short m_CompressionThreshold;
    int m_CompressionAlgorithm;
    bool m_OnlineMode;
    bool m_AllowList;
    bool m_IsVisibleToLan;

public:
    explicit PropertiesSettings(const std::string& name);

    bool isPropertiesFileLoaded() const { return this->m_IsLoaded; };
    const std::string& getCustomProperty(const std::string& name) { return this->m_CustomProperties[name]; };

    static bool parseBoolean(const std::string& buffer) { return buffer == "true"; };
    static int parseInt(const std::string& buffer) { return std::strtol(buffer.c_str(), 0, 0); };

    GameType getGameMode() const;
    Difficulty getDifficulty() const;
    const std::string& getServerName() const { return this->m_ServerName; };
    int getMaxPlayers() const { return this->m_MaxPlayers; };
    int getOpPermissionLevel() const;
    unsigned short getServerPort() const { return this->m_ServerPort; };
    unsigned short getServerPortV6() const { return this->m_ServerPortV6; };
    const std::string& getLevelName() const { return this->m_LevelName; };
    const std::string& getLevelSeed() const { return this->m_LevelSeed; };
    bool forceGameMode() const { return this->m_ForceGameMode; };
    bool allowCheats() const { return this->m_AllowCheats; };
    bool getServerTickRange() const { return this->m_TickDistance; };
    PlayerTickPolicy getPlayerTickPolicy() const;
    int getDefaultPlayerPermissionLevel() const;
    int getChatRestrictionLevel() const { return this->m_ChatRestrictionLevel; };
    bool useAllowList() const { return this->m_AllowList; };
    bool useOnlineAuthentication() const { return this->m_OnlineMode; };
    bool isServerVisibleToLanDiscovery() const { return this->m_IsVisibleToLan; };
};

#endif // !PROPERTIES_SETTINGS_HPP
