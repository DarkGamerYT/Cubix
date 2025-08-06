#ifndef GAMERULES_HPP
#define GAMERULES_HPP

#include <vector>

#include "GameRule.hpp"

class GameRules {
private:
    std::vector<std::shared_ptr<IGameRule>> mGameRules;

public:
    GameRules() = default;

    void initialize();
    void registerGameRule(const IGameRule& gameRule);

    std::vector<std::shared_ptr<IGameRule>> getRules() const { return this->mGameRules; };

public:
    static GameRule<bool> CommandBlockOutput;
    static GameRule<bool> DoDaylightCycle;
    static GameRule<bool> DoEntityDrops;
    static GameRule<bool> DoFireTick;
    static GameRule<bool> RecipesUnlock;
    static GameRule<bool> DoLimitedCrafting;
    static GameRule<bool> DoMobLoot;
    static GameRule<bool> DoMobSpawning;
    static GameRule<bool> DoTileDrops;
    static GameRule<bool> DoWeatherCycle;
    static GameRule<bool> DrowningDamage;
    static GameRule<bool> FallDamage;
    static GameRule<bool> FireDamage;
    static GameRule<bool> KeepInventory;
    static GameRule<bool> MobGriefing;
    static GameRule<bool> PVP;
    static GameRule<bool> ShowCoordinates;
    static GameRule<bool> ShowDaysPlayed;
    static GameRule<bool> DoNaturalRegeneration;
    static GameRule<bool> DoTntExplode;
    static GameRule<bool> SendCommandFeedback;
    static GameRule<bool> LocatorBar;
    static GameRule<int> MaxCommandChainLength;
    static GameRule<bool> DoInsomnia;
    static GameRule<bool> CommandBlocksEnabled;
    static GameRule<int> RandomTickSpeed;
    static GameRule<bool> DoImmediateRespawn;
    static GameRule<bool> ShowDeathMessages;
    static GameRule<int> FunctionCommandLimit;
    static GameRule<int> PlayerSpawnRadius;
    static GameRule<bool> ShowTags;
    static GameRule<bool> FreezeDamage;
    static GameRule<bool> RespawnBlocksExplode;
    static GameRule<bool> ShowBorderEffect;
    static GameRule<bool> ShowRecipeMessages;
    static GameRule<int> PlayerSleepingPercentage;
    static GameRule<bool> ProjectilesCanBreakBlocks;
    static GameRule<bool> TntExplosionDropDecay;
};

#endif //GAMERULES_HPP
