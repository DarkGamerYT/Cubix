#include "Level.hpp"
void Level::initialize(const LevelSettings& levelSettings) {
    this->mLevelSettings = std::make_shared<LevelSettings>(levelSettings);

    const LevelSeed64& seed = this->mLevelSettings->getSeed();
    this->mRandom = Random{ static_cast<uint32_t>(seed.getSeed()) };

    Logger::log(Logger::LogLevel::Debug, "Level Seed: {}", seed.toString());

    {
        // Testing purposes
        auto& experiments = this->mLevelSettings->getExperiments();
        experiments.emplace("upcoming_creator_features", true);
        experiments.emplace("gametest", true);
        this->mLevelSettings->setHasHadExperiments(true);
    };
};

void Level::tick(const uint32_t tick) {
    // Logger::log(Logger::LogLevel::Debug, "Current tick: {}", tick);
};