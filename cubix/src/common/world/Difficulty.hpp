#ifndef DIFFICULTY_HPP
#define DIFFICULTY_HPP

#include <string>

enum class Difficulty
{
    Peaceful = 0,
    Easy     = 1,
    Normal   = 2,
    Hard     = 3
};

class DifficultyUtils
{
public:
    static std::string asString(Difficulty);
};

#endif // !DIFFICULTY_HPP