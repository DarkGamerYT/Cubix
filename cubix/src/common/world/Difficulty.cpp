#include "Difficulty.hpp"
std::string DifficultyUtils::asString(const Difficulty value)
{
    switch (value)
    {
    case Difficulty::Peaceful:
        return "PEACEFUL";
    case Difficulty::Easy:
        return "EASY";
    case Difficulty::Normal:
        return "NORMAL";
    case Difficulty::Hard:
        return "HARD";

    default:
        return "UNKNOWN";
    };
};