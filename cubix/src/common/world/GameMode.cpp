#include "GameMode.hpp"
GameMode::GameMode()
{

};
GameMode::~GameMode()
{

};

std::string GameMode::asString(const GameType value)
{
    switch (value)
    {
        case GameType::Default:
        case GameType::Survival:
            return "Survival";
        case GameType::Creative:
            return "Creative";
        case GameType::Adventure:
            return "Adventure";
        case GameType::Spectator:
            return "Spectator";

        default:
            return "Unknown";
    };
};