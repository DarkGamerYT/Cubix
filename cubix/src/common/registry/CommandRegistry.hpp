#ifndef COMMANDREGISTRY_HPP
#define COMMANDREGISTRY_HPP
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include <string>

#include "../server/commands/Command.hpp"
#include "ItemRegistry.hpp"

class CommandRegistry
{
public:
    using Commands = std::unordered_map<std::string, std::shared_ptr<Command>>;

private:
    static inline const std::vector<std::string> GAMEMODES = { "survival", "s", "creative", "c", "adventure", "a", "spectator" };

public:
    static void initialize(const bool isEdu)
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

    static const Commands& getAll() { return CommandRegistry::s_Commands; };

    template <typename T>
    static void registerCommand(const std::string& name, const CommandPermissionLevel permissionLevel) {
        static_assert(std::is_base_of_v<Command, T>, "T must inherit from Command");

        const auto& command = std::make_shared<T>(permissionLevel);
        command->setup();

        CommandRegistry::s_Commands.emplace(name, command);
    };

    // Post fixes
    static const std::vector<std::string>& getPostFixes() { return CommandRegistry::s_PostFixes; };

    static uint64_t addPostfix(const std::string& name) {
        s_PostFixes.emplace_back(name);
        return s_PostFixes.size() - 1;
    };

    // Enums
    static const std::vector<std::string>& getEnums() { return CommandRegistry::s_Enums; };
    static const std::vector<std::string>& getAllEnumValues() { return CommandRegistry::s_EnumValues; };

    static uint64_t getEnum(const std::string& value) {
        if (const auto it = std::ranges::find(s_Enums, value); it != s_Enums.end())
            return static_cast<uint64_t>(std::distance(s_Enums.begin(), it));

        return -1;
    };

    static uint64_t addEnum(const std::string& name, const std::vector<std::string>& values) {
        std::vector<uint64_t> indexes;
        for (const auto& value : values)
        {
            s_EnumValues.emplace_back(value);
            indexes.emplace_back(s_EnumValues.size() - 1);
        };

        s_EnumLookup.emplace(name, indexes);
        s_Enums.emplace_back(name);
        return s_Enums.size() - 1;
    };

    // Enum values
    static const std::vector<uint64_t>& getEnumValues(const std::string& name) {
        return CommandRegistry::s_EnumLookup[name];
    };

    static void setEnumValues(const std::string& name, const std::vector<std::string>& values) {
        for (const uint64_t index : getEnumValues(name))
            s_EnumValues.erase(s_EnumValues.begin() + static_cast<std::vector<uint64_t>::difference_type>(index));

        std::vector<uint64_t> indexes;
        for (const auto& value : values)
        {
            s_EnumValues.emplace_back(value);
            indexes.emplace_back(s_EnumValues.size() - 1);
        };

        s_EnumLookup[name] = indexes;
    };

    // Soft Enums
    static const std::vector<std::string>& getSoftEnums() { return CommandRegistry::s_SoftEnums; };
    static const std::vector<std::string>& getAllSoftEnumValues() { return CommandRegistry::s_SoftEnumValues; };

    static uint64_t getSoftEnum(const std::string& value) {
        if (const auto it = std::ranges::find(s_SoftEnums, value); it != s_SoftEnums.end())
            return static_cast<uint64_t>(std::distance(s_SoftEnums.begin(), it));

        return -1;
    };

    static uint64_t addSoftEnum(const std::string& name, const std::vector<std::string>& values) {
        std::vector<uint64_t> indexes;
        for (const auto& value : values)
        {
            s_SoftEnumValues.emplace_back(value);
            indexes.emplace_back(s_SoftEnumValues.size() - 1);
        };

        s_SoftEnumLookup.emplace(name, indexes);
        s_SoftEnums.emplace_back(name);
        return s_SoftEnums.size() - 1;
    };

    // Soft Enums values
    static const std::vector<uint64_t>& getSoftEnumValues(const std::string& name) {
        return CommandRegistry::s_SoftEnumLookup[name];
    };

    static void setSoftEnumValues(const std::string& name, const std::vector<std::string>& values) {
        for (const uint64_t index : getSoftEnumValues(name))
            s_SoftEnumValues.erase(s_SoftEnumValues.begin() + static_cast<std::vector<uint64_t>::difference_type>(index));

        std::vector<uint64_t> indexes;
        for (const auto& value : values)
        {
            s_SoftEnumValues.emplace_back(value);
            indexes.emplace_back(s_SoftEnumValues.size() - 1);
        };

        s_SoftEnumLookup[name] = indexes;
    };

protected:
    static inline Commands s_Commands = {};
    static inline std::vector<std::string> s_PostFixes = {};

    typedef std::unordered_map<std::string, std::vector<uint64_t>> EnumValues;

    static inline std::vector<std::string> s_Enums = {};
    static inline EnumValues s_EnumLookup = {};
    static inline std::vector<std::string> s_EnumValues = {};

    static inline std::vector<std::string> s_SoftEnums = {};
    static inline EnumValues s_SoftEnumLookup = {};
    static inline std::vector<std::string> s_SoftEnumValues = {};
};

#endif // !COMMANDREGISTRY_HPP