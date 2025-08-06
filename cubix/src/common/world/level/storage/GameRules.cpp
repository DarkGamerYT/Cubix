#include "GameRules.hpp"

#include <memory>

void GameRules::initialize() {
    this->registerGameRule(GameRules::CommandBlockOutput);
    this->registerGameRule(GameRules::DoDaylightCycle);
    this->registerGameRule(GameRules::DoEntityDrops);
    this->registerGameRule(GameRules::DoFireTick);
    this->registerGameRule(GameRules::RecipesUnlock);
    this->registerGameRule(GameRules::DoLimitedCrafting);
    this->registerGameRule(GameRules::DoMobLoot);
    this->registerGameRule(GameRules::DoMobSpawning);
    this->registerGameRule(GameRules::DoTileDrops);
    this->registerGameRule(GameRules::DoWeatherCycle);
    this->registerGameRule(GameRules::DrowningDamage);
    this->registerGameRule(GameRules::FallDamage);
    this->registerGameRule(GameRules::FireDamage);
    this->registerGameRule(GameRules::KeepInventory);
    this->registerGameRule(GameRules::MobGriefing);
    this->registerGameRule(GameRules::PVP);
    this->registerGameRule(GameRules::ShowCoordinates);
    this->registerGameRule(GameRules::ShowDaysPlayed);
    this->registerGameRule(GameRules::DoNaturalRegeneration);
    this->registerGameRule(GameRules::DoTntExplode);
    this->registerGameRule(GameRules::SendCommandFeedback);
    this->registerGameRule(GameRules::LocatorBar);
    this->registerGameRule(GameRules::MaxCommandChainLength);
    this->registerGameRule(GameRules::DoInsomnia);
    this->registerGameRule(GameRules::CommandBlocksEnabled);
    this->registerGameRule(GameRules::RandomTickSpeed);
    this->registerGameRule(GameRules::DoImmediateRespawn);
    this->registerGameRule(GameRules::ShowDeathMessages);
    this->registerGameRule(GameRules::FunctionCommandLimit);
    this->registerGameRule(GameRules::PlayerSpawnRadius);
    this->registerGameRule(GameRules::ShowTags);
    this->registerGameRule(GameRules::FreezeDamage);
    this->registerGameRule(GameRules::RespawnBlocksExplode);
    this->registerGameRule(GameRules::ShowBorderEffect);
    this->registerGameRule(GameRules::ShowRecipeMessages);
    this->registerGameRule(GameRules::PlayerSleepingPercentage);
    this->registerGameRule(GameRules::ProjectilesCanBreakBlocks);
    this->registerGameRule(GameRules::TntExplosionDropDecay);
};

void GameRules::registerGameRule(const IGameRule& gameRule) {
    this->mGameRules.emplace_back(gameRule.clone());
};

GameRule<bool> GameRules::CommandBlockOutput { "commandblockoutput", true };
GameRule<bool> GameRules::DoDaylightCycle { "dodaylightcycle", true };
GameRule<bool> GameRules::DoEntityDrops { "doentitydrops", true };
GameRule<bool> GameRules::DoFireTick { "dofiretick", true };
GameRule<bool> GameRules::RecipesUnlock { "recipesunlock", true };
GameRule<bool> GameRules::DoLimitedCrafting { "dolimitedcrafting", false };
GameRule<bool> GameRules::DoMobLoot { "domobloot", true };
GameRule<bool> GameRules::DoMobSpawning { "domobspawning", true };
GameRule<bool> GameRules::DoTileDrops { "dotiledrops", true };
GameRule<bool> GameRules::DoWeatherCycle { "doweathercycle", true };
GameRule<bool> GameRules::DrowningDamage { "drowningdamage", true };
GameRule<bool> GameRules::FallDamage { "falldamage", true };
GameRule<bool> GameRules::FireDamage { "firedamage", true };
GameRule<bool> GameRules::KeepInventory { "keepinventory", false };
GameRule<bool> GameRules::MobGriefing { "mobgriefing", true };
GameRule<bool> GameRules::PVP { "pvp", true };
GameRule<bool> GameRules::ShowCoordinates { "showcoordinates", true };
GameRule<bool> GameRules::ShowDaysPlayed { "showdaysplayed", true };
GameRule<bool> GameRules::DoNaturalRegeneration { "donaturalregeneration", true };
GameRule<bool> GameRules::DoTntExplode { "dotntexplode", true };
GameRule<bool> GameRules::SendCommandFeedback { "sendcommandfeedback", true };
GameRule<bool> GameRules::LocatorBar { "locatorbar", true };
GameRule<int> GameRules::MaxCommandChainLength { "maxcommandchainlength", 65535 };
GameRule<bool> GameRules::DoInsomnia { "doinsomnia", true };
GameRule<bool> GameRules::CommandBlocksEnabled { "commandblocksenabled", false };
GameRule<int> GameRules::RandomTickSpeed { "randomtickspeed", 3 };
GameRule<bool> GameRules::DoImmediateRespawn { "doimmediaterespawn", false };
GameRule<bool> GameRules::ShowDeathMessages { "showdeathmessages", true };
GameRule<int> GameRules::FunctionCommandLimit { "functioncommandlimit", 10000 };
GameRule<int> GameRules::PlayerSpawnRadius { "spawnradius", 10 };
GameRule<bool> GameRules::ShowTags { "showtags", true };
GameRule<bool> GameRules::FreezeDamage { "freezedamage", true };
GameRule<bool> GameRules::RespawnBlocksExplode { "respawnblocksexplode", true };
GameRule<bool> GameRules::ShowBorderEffect { "showbordereffect", true };
GameRule<bool> GameRules::ShowRecipeMessages { "showrecipemessages", true };
GameRule<int> GameRules::PlayerSleepingPercentage { "playersleepingpercentage", 100 };
GameRule<bool> GameRules::ProjectilesCanBreakBlocks { "projectilescanbreakblocks", true };
GameRule<bool> GameRules::TntExplosionDropDecay { "tntexplosiondropdecay", false };