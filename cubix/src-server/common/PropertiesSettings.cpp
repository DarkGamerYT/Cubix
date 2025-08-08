#include "PropertiesSettings.hpp"

static std::string trim(std::string& value)
{
    value.erase(0, std::min(value.find_first_not_of(" \t"), value.size()));
    value.erase(0, value.size() - value.find_last_not_of(" \t") - 1);

    return value;
};

PropertiesSettings::PropertiesSettings(const std::string& name)
{
    std::ifstream file(name);
    if (!file.is_open())
    {
        this->mIsLoaded = false;
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
                    Util::toLower(v);
                    if (v == "creative" || v == "1" || v == "c")
                        this->mGameMode = GameType::Creative;

                    else if (v == "adventure" || v == "2" || v == "a")
                        this->mGameMode = GameType::Adventure;

                    else if (v == "spectator")
                        this->mGameMode = GameType::Spectator;

                    else this->mGameMode = GameType::Survival;
                }
            },

            { "difficulty",
                [this](const std::string& v) {
                    Util::toLower(v);
                    if (v == "peaceful" || v == "0")
                        this->mDifficulty = Difficulty::Peaceful;

                    else if (v == "normal" || v == "2")
                        this->mDifficulty = Difficulty::Normal;

                    else if (v == "hard" || v == "3")
                        this->mDifficulty = Difficulty::Hard;

                    else this->mDifficulty = Difficulty::Easy;
                }
            },

            { "server-name",
                [this](const std::string& v) { this->mServerName = v; } },

            { "max-players",
                [this](const std::string& v) { this->mMaxPlayers = PropertiesSettings::parseInt(v); } },

            { "op-permission-level",
                [this](const std::string& v) {
                    const int value = PropertiesSettings::parseInt(v);
                    if (value <= 4)
                        this->mOpPermissionLevel = static_cast<CommandPermissionLevel>(value);

                    else this->mOpPermissionLevel = CommandPermissionLevel::GameDirectors;
                }
            },

            { "server-port",
                [this](const std::string& v) { this->mServerPort = PropertiesSettings::parseInt(v); } },

            { "server-portv6",
                [this](const std::string& v) { this->mServerPortV6 = PropertiesSettings::parseInt(v); } },

            { "level-name",
                [this](const std::string& v) { this->mLevelName = v; } },

            { "level-seed",
                [this](const std::string& v) { this->mLevelSeed = v; } },

            { "force-gamemode",
                [this](const std::string& v) { this->mForceGameMode = PropertiesSettings::parseBoolean(v); } },

            { "allow-cheats",
                [this](const std::string& v) { this->mAllowCheats = PropertiesSettings::parseBoolean(v); } },

            { "tick-distance",
                [this](const std::string& v) { this->mTickDistance = PropertiesSettings::parseInt(v); } },

            { "player-tick-policy",
                [this](const std::string& v) {
                    Util::toLower(v);
                    if (v == "throttled")
                        this->mPlayerTickPolicy = PlayerTickPolicy::THROTTLED;

                    else this->mPlayerTickPolicy = PlayerTickPolicy::GREEDY;
            }
            },

            { "transport-layer-type",
                [this](const std::string& v) {
                    Util::toLower(v);
                    if (v == "raknet")
                        this->mTransportLayer = TransportLayer::RakNet;
                    else if (v == "nethernet")
                        this->mTransportLayer = TransportLayer::NetherNet;

                    else this->mTransportLayer = TransportLayer::Default;
            }
            },

            { "allow-list",
                [this](const std::string& v) { this->mAllowList = PropertiesSettings::parseBoolean(v); } },

            { "online-mode",
                [this](const std::string& v) { this->mOnlineMode = PropertiesSettings::parseBoolean(v); } },

            { "enable-lan-visibility",
                [this](const std::string& v) { this->mIsVisibleToLan = PropertiesSettings::parseBoolean(v); } },

            { "compression-threshold",
                [this](const std::string& v) { this->mCompressionThreshold = static_cast<short>(PropertiesSettings::parseInt(v)); } },

            { "chat-restriction",
                [this](const std::string& v) {
                    Util::toLower(v);
                    if (v == "dropped")
                        this->mChatRestrictionLevel = ChatRestrictionLevel::Dropped;
                    else if (v == "disabled")
                        this->mChatRestrictionLevel = ChatRestrictionLevel::Disabled;
                    else this->mChatRestrictionLevel = ChatRestrictionLevel::None;
                }
            },

            { "compression-algorithm",
                [this](const std::string& v) {
                    Util::toLower(v);
                    if (v == "zlib")
                        this->mCompressionAlgorithm = CompressionType::Zlib;
                    else if (v == "snappy")
                        this->mCompressionAlgorithm = CompressionType::Snappy;
                    else this->mCompressionAlgorithm = CompressionType::None;
                }
            },

            { "default-player-permission-level",
                [this](const std::string& v) {
                    Util::toLower(v);
                    if (v == "member")
                        this->mDefaultPermissionLevel = PlayerPermissionLevel::Member;
                    else if (v == "operator")
                        this->mDefaultPermissionLevel = PlayerPermissionLevel::Operator;

                    else this->mDefaultPermissionLevel = PlayerPermissionLevel::Visitor;
                }
            },
        };

        const auto it = actions.find(key);
        if (it != actions.end()) {
            it->second(value);
        }
        else {
            this->mCustomProperties[key] = value;
        };
    };

    this->mIsLoaded = true;
};