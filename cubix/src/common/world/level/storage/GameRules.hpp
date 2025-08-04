#ifndef GAMERULES_HPP
#define GAMERULES_HPP

#include <vector>

#include "GameRule.hpp"

class GameRules {
private:
    std::vector<GameRule> mGameRules;

public:
    GameRules() = default;

    void initialize();

    std::vector<GameRule> getRules() const { return this->mGameRules; };

public:
    static GameRule CommandBlockOutput;
    static GameRule DoDaylightCycle;
    static GameRule DoEntityDrops;
    static GameRule DoFireTick;
    static GameRule RecipesUnlock;
    static GameRule DoLimitedCrafting;
    static GameRule DoMobLoot;
    static GameRule DoMobSpawning;
    static GameRule DoTileDrops;
    static GameRule DoWeatherCycle;
    static GameRule DrowningDamage;
    static GameRule FallDamage;
    static GameRule FireDamage;
    static GameRule KeepInventory;
    static GameRule MobGriefing;
    static GameRule Pvp;
    static GameRule ShowCoordinates;
    static GameRule ShowDaysPlayed;
    static GameRule DoNaturalRegeneration;
    static GameRule DoTntExplode;
    static GameRule SendCommandFeedback;
    static GameRule LocatorBar;
    static GameRule MaxCommandChainLength;
    static GameRule DoInsomnia;
    static GameRule CommandBlocksEnabled;
    static GameRule RandomTickSpeed;
    static GameRule DoImmediateRespawn;
    static GameRule ShowDeathMessages;
    static GameRule FunctionCommandLimit;
    static GameRule PlayerSpawnRadius;
    static GameRule ShowTags;
    static GameRule FreezeDamage;
    static GameRule RespawnBlocksExplode;
    static GameRule ShowBorderEffect;
    static GameRule ShowRecipeMessages;
    static GameRule PlayerSleepingPercentage;
    static GameRule ProjectilesCanBreakBlocks;
    static GameRule TntExplosionDropDecay;
};

#endif //GAMERULES_HPP
