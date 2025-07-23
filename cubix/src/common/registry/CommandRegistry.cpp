#include "CommandRegistry.hpp"
void CommandRegistry::initialize(const bool isEdu)
{
    CommandRegistry::addSoftEnum("Boolean", { "true", "false" });
    CommandRegistry::addSoftEnum("GameMode", GAMEMODES);

    CommandRegistry::addEnum("Block", {});
    CommandRegistry::addEnum("Item", {});
    CommandRegistry::addEnum("Entity", {});

    if (true == isEdu)
    {
        // TODO: Register education edition stuff
    };
};

// Enums
uint64_t CommandRegistry::getEnum(const std::string& value) {
    if (const auto it = std::ranges::find(sEnums, value); it != sEnums.end())
        return static_cast<uint64_t>(std::distance(sEnums.begin(), it));

    return -1;
};

uint64_t CommandRegistry::addEnum(const std::string& name, const std::vector<std::string>& values) {
    std::vector<uint64_t> indexes;
    for (const auto& value : values)
    {
        sEnumValues.emplace_back(value);
        indexes.emplace_back(sEnumValues.size() - 1);
    };

    sEnumLookup.emplace(name, indexes);
    sEnums.emplace_back(name);
    return sEnums.size() - 1;
};

// Enum values
void CommandRegistry::setEnumValues(const std::string& name, const std::vector<std::string>& values) {
    for (const uint64_t index : getEnumValues(name))
        sEnumValues.erase(sEnumValues.begin() + static_cast<std::vector<uint64_t>::difference_type>(index));

    std::vector<uint64_t> indexes;
    for (const auto& value : values)
    {
        sEnumValues.emplace_back(value);
        indexes.emplace_back(sEnumValues.size() - 1);
    };

    sEnumLookup[name] = indexes;
};

// Soft Enums
uint64_t CommandRegistry::getSoftEnum(const std::string& value) {
    if (const auto it = std::ranges::find(sSoftEnums, value); it != sSoftEnums.end())
        return static_cast<uint64_t>(std::distance(sSoftEnums.begin(), it));

    return -1;
};

uint64_t CommandRegistry::addSoftEnum(const std::string& name, const std::vector<std::string>& values) {
    std::vector<uint64_t> indexes;
    for (const auto& value : values)
    {
        sSoftEnumValues.emplace_back(value);
        indexes.emplace_back(sSoftEnumValues.size() - 1);
    };

    sSoftEnumLookup.emplace(name, indexes);
    sSoftEnums.emplace_back(name);
    return sSoftEnums.size() - 1;
};

// Soft Enums values
void CommandRegistry::setSoftEnumValues(const std::string& name, const std::vector<std::string>& values) {
    for (const uint64_t index : getSoftEnumValues(name))
        sSoftEnumValues.erase(sSoftEnumValues.begin() + static_cast<std::vector<uint64_t>::difference_type>(index));

    std::vector<uint64_t> indexes;
    for (const auto& value : values)
    {
        sSoftEnumValues.emplace_back(value);
        indexes.emplace_back(sSoftEnumValues.size() - 1);
    };

    sSoftEnumLookup[name] = indexes;
};

std::vector<std::string> CommandRegistry::GAMEMODES = { "survival", "s", "creative", "c", "adventure", "a", "spectator" };