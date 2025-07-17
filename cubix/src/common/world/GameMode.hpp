#ifndef GAMEMODE_HPP
#define GAMEMODE_HPP

#include <string>

enum class GameType : int {
    Undefined    = -1,
    Survival     = 0,
    Creative     = 1,
    Adventure    = 2,
    Default      = 5,
    Spectator    = 6,
    WorldDefault = 0
};

class GameMode
{
private:

public:
    GameMode();
    ~GameMode();

    static std::string asString(GameType);
};

#endif // !GAMEMODE_HPP