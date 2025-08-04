#include "PropertiesSettings.hpp"

static std::string trim(std::string& value)
{
    value.erase(0, std::min(value.find_first_not_of(" \t"), value.size()));
    value.erase(0, value.size() - value.find_last_not_of(" \t") - 1);

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
        Util::toLower(key);

        if (const size_t commentPos = value.find('#');
            commentPos != std::string::npos)
            value = value.substr(0, commentPos);

        // Trim the value
        trim(value);

        static const std::unordered_map<std::string, std::function<void(std::string)>> actions = {
            { "gamemode",
                [this](const std::string& v) {
                    Util::toLower(this->m_GameMode);
                    this->m_GameMode = v;
                }
            },

            { "difficulty",
                [this](const std::string& v) {
                    Util::toLower(this->m_Difficulty);
                    this->m_Difficulty = v;
                }
            },

            { "server-name",
                [this](const std::string& v) { this->m_ServerName = v; } },

            { "max-players",
                [this](const std::string& v) { this->m_MaxPlayers = PropertiesSettings::parseInt(v); } },

            { "op-permission-level",
                [this](const std::string& v) { this->m_OpPermissionLevel = PropertiesSettings::parseInt(v); } },

            { "server-port",
                [this](const std::string& v) { this->m_ServerPort = PropertiesSettings::parseInt(v); } },

            { "server-portv6",
                [this](const std::string& v) { this->m_ServerPortV6 = PropertiesSettings::parseInt(v); } },

            { "level-name",
                [this](const std::string& v) { this->m_LevelName = v; } },

            { "level-seed",
                [this](const std::string& v) { this->m_LevelSeed = v; } },

            { "force-gamemode",
                [this](const std::string& v) { this->m_ForceGameMode = PropertiesSettings::parseBoolean(v); } },

            { "allow-cheats",
                [this](const std::string& v) { this->m_AllowCheats = PropertiesSettings::parseBoolean(v); } },

            { "tick-distance",
                [this](const std::string& v) { this->m_TickDistance = PropertiesSettings::parseInt(v); } },

            { "player-tick-policy",
                [this](const std::string& v) {
                    Util::toLower(this->m_PlayerTickPolicy);
                    this->m_PlayerTickPolicy = v;
                }
            },

            { "allow-list",
                [this](const std::string& v) { this->m_AllowList = PropertiesSettings::parseBoolean(v); } },

            { "online-mode",
                [this](const std::string& v) { this->m_OnlineMode = PropertiesSettings::parseBoolean(v); } },

            { "enable-lan-visibility",
                [this](const std::string& v) { this->m_IsVisibleToLan = PropertiesSettings::parseBoolean(v); } },

            { "compression-threshold",
                [this](const std::string& v) { this->m_CompressionThreshold = static_cast<short>(PropertiesSettings::parseInt(v)); } },

            { "chat-restriction",
                [this](const std::string& v) {
                    Util::toLower(v);
                    if (v == "dropped")
                        this->m_ChatRestrictionLevel = 1;
                    else if (v == "disabled")
                        this->m_ChatRestrictionLevel = 2;
                    else this->m_ChatRestrictionLevel = 0;
                }
            },

            { "compression-algorithm",
                [this](const std::string& v) {
                    Util::toLower(v);
                    if (v == "zlib")
                        this->m_CompressionAlgorithm = 0x01;
                    else if (v == "snappy")
                        this->m_CompressionAlgorithm = 0x02;
                    else this->m_CompressionAlgorithm = 0x00;
                }
            },

            { "default-player-permission-level",
                [this](const std::string& v) {
                    Util::toLower(this->m_DefaultPermissionLevel);
                    this->m_DefaultPermissionLevel = v;
                }
            },
        };

        const auto it = actions.find(key);
        if (it != actions.end()) {
            it->second(value);
        }
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
        return GameType::Creative;

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