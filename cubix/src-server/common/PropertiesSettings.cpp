#include "PropertiesSettings.hpp"
static std::string trim(std::string& value)
{
    value.erase(0, std::min(value.find_first_not_of(" \t"), value.size()));
    value.erase(0, value.size() - value.find_last_not_of(" \t") - 1);

    std::ranges::transform(
        value, value.begin(),
        [](const unsigned char c) { return std::tolower(c); }
    );

    return value;
};

PropertiesSettings::PropertiesSettings(const std::string& name)
{
    this->m_LevelName = "level";
    this->m_ServerName = "Dedicated Server";
    this->m_MaxPlayers = 10;
    this->m_ServerPort = 19132;
    this->m_ServerPortV6 = 19133;
    this->m_GameMode = "survival";
    this->m_Difficulty = "normal";
    this->m_OpPermissionLevel = 1;
    this->m_ChatRestrictionLevel = 0;
    this->m_CompressionThreshold = 0;
    this->m_CompressionAlgorithm = 0x00;
    this->m_ForceGameMode = false;
    this->m_AllowCheats = false;
    this->m_TickDistance = 4;
    this->m_DefaultPermissionLevel = "member";
    this->m_PlayerTickPolicy = "greedy";
    this->m_OnlineMode = true;
    this->m_AllowList = false;
    this->m_IsVisibleToLan = true;

    std::ifstream file(name);
    if (!file.is_open())
    {
        this->m_IsLoaded = false;
        return;
    };

    std::string line;
    while (std::getline(file, line))
    {
        line.erase(0, std::min(line.find_first_not_of(" \t"), line.size()));
        if (line.empty() || line[0] == '#')
            continue;

        const size_t delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos)
            continue;

        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);

        if (key.find('#') != std::string::npos)
            continue;
        // Trim the key
        trim(key);

        if (const size_t commentPos = value.find('#');
            commentPos != std::string::npos)
            value = value.substr(0, commentPos);

        // Trim the value
        trim(value);

        if (key == "gamemode")
            this->m_GameMode = value;

        else if (key == "difficulty")
            this->m_Difficulty = value;

        else if (key == "server-name")
            this->m_ServerName = value;

        else if (key == "max-players")
            this->m_MaxPlayers = PropertiesSettings::parseInt(value);

        else if (key == "op-permission-level")
            this->m_OpPermissionLevel = PropertiesSettings::parseInt(value);

        else if (key == "server-port")
            this->m_ServerPort = PropertiesSettings::parseInt(value);

        else if (key == "server-portv6")
            this->m_ServerPortV6 = PropertiesSettings::parseInt(value);

        else if (key == "level-name")
            this->m_LevelName = value;

        else if (key == "level-seed")
            this->m_LevelSeed = value;

        else if (key == "force-gamemode")
            this->m_ForceGameMode = PropertiesSettings::parseBoolean(value);

        else if (key == "allow-cheats")
            this->m_AllowCheats = PropertiesSettings::parseBoolean(value);

        else if (key == "tick-distance")
            this->m_TickDistance = PropertiesSettings::parseInt(value);

        else if (key == "default-player-permission-level")
        {
            this->m_DefaultPermissionLevel = value;
        }
        else if (key == "player-tick-policy")
        {
            this->m_PlayerTickPolicy = value;
        }

        else if (key == "chat-restriction")
        {
            if (value == "dropped")
                this->m_ChatRestrictionLevel = 1;
            else if (value == "disabled")
                this->m_ChatRestrictionLevel = 2;
            else this->m_ChatRestrictionLevel = 0;
        }

        else if (key == "compression-threshold")
            this->m_CompressionThreshold = static_cast<short>(PropertiesSettings::parseInt(value));

        else if (key == "compression-algorithm")
        {
            if (value == "zlib")
                this->m_CompressionAlgorithm = 0x01;
            else if (value == "snappy")
                this->m_CompressionAlgorithm = 0x02;
            else this->m_CompressionAlgorithm = 0x00;
        }

        else if (key == "allow-list")
            this->m_AllowList = PropertiesSettings::parseBoolean(value);

        else if (key == "online-mode")
            this->m_OnlineMode = PropertiesSettings::parseBoolean(value);

        else if (key == "enable-lan-visibility")
            this->m_IsVisibleToLan = PropertiesSettings::parseBoolean(value);
        
        else {
            this->m_CustomProperties[key] = value;
        };
    };

    this->m_IsLoaded = true;
};

int PropertiesSettings::getDefaultPlayerPermissionLevel() const
{
    if (this->m_DefaultPermissionLevel == "operator")
        return 2;
    else if (this->m_DefaultPermissionLevel == "visitor")
        return 1;

    return 0;
};

int PropertiesSettings::getOpPermissionLevel() const
{
    if (this->m_OpPermissionLevel <= 4)
        return this->m_OpPermissionLevel;

    return 1;
};

GameType PropertiesSettings::getGameMode() const
{
    if (this->m_GameMode == "creative" || this->m_GameMode == "1" || this->m_GameMode == "c")
        return GameType::Survival;

    else if (this->m_GameMode == "adventure" || this->m_GameMode == "2" || this->m_GameMode == "a")
        return GameType::Adventure;
    
    else if (this->m_GameMode == "spectator")
        return GameType::Spectator;

    return GameType::Survival;
};

Difficulty PropertiesSettings::getDifficulty() const
{
    if (this->m_Difficulty == "peaceful" || this->m_Difficulty == "0")
        return Difficulty::Peaceful;

    else if (this->m_Difficulty == "normal" || this->m_Difficulty == "2")
        return Difficulty::Normal;
    
    else if (this->m_Difficulty == "hard" || this->m_Difficulty == "3")
        return Difficulty::Hard;
    
    return Difficulty::Easy;
};


PlayerTickPolicy PropertiesSettings::getPlayerTickPolicy() const {
    if (this->m_PlayerTickPolicy == "throttled")
        return PlayerTickPolicy::THROTTLED;

    return PlayerTickPolicy::GREEDY;
};