#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "LevelSettings.hpp"
#include "storage/LevelSeed64.hpp"
#include "../../util/random/Random.hpp"

class Level {
private:
    std::shared_ptr<LevelSettings> mLevelSettings;
    Random mRandom{};

public:
    void initialize(const LevelSettings&);

    std::shared_ptr<LevelSettings> getLevelSettings() const { return this->mLevelSettings; };
};

#endif //LEVEL_HPP
