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
    static std::vector<std::string> GAMEMODES;

public:
    static void initialize(const bool isEdu);

    template <typename T>
    static void registerCommand(const std::string& name, const CommandPermissionLevel permissionLevel) {
        static_assert(std::is_base_of_v<Command, T>, "T must inherit from Command");

        const auto& command = std::make_shared<T>(permissionLevel);
        command->setup();

        CommandRegistry::sCommands.emplace(name, command);
    };

    static const Commands& getAll() { return CommandRegistry::sCommands; };

    // Post fixes
    static const std::vector<std::string>& getPostFixes() { return CommandRegistry::sPostFixes; };

    static uint64_t addPostfix(const std::string& name) {
        sPostFixes.emplace_back(name);
        return sPostFixes.size() - 1;
    };

    // Enums
    static const std::vector<std::string>& getEnums() { return CommandRegistry::sEnums; };
    static const std::vector<std::string>& getAllEnumValues() { return CommandRegistry::sEnumValues; };

    static uint64_t getEnum(const std::string& value);
    static uint64_t addEnum(const std::string& name, const std::vector<std::string>& values);

    // Enum values
    static const std::vector<uint64_t>& getEnumValues(const std::string& name) {
        return sEnumLookup[name];
    };

    static void setEnumValues(const std::string& name, const std::vector<std::string>& values);

    // Soft Enums
    static const std::vector<std::string>& getSoftEnums() { return sSoftEnums; };
    static const std::vector<std::string>& getAllSoftEnumValues() { return sSoftEnumValues; };

    static uint64_t getSoftEnum(const std::string& value);
    static uint64_t addSoftEnum(const std::string& name, const std::vector<std::string>& values);

    // Soft Enums values
    static const std::vector<uint64_t>& getSoftEnumValues(const std::string& name) {
        return sSoftEnumLookup[name];
    };

    static void setSoftEnumValues(const std::string& name, const std::vector<std::string>& values);

protected:
    static inline Commands sCommands{};
    static inline std::vector<std::string> sPostFixes{};

    typedef std::unordered_map<std::string, std::vector<uint64_t>> EnumValues;

    static inline std::vector<std::string> sEnums{};
    static inline EnumValues sEnumLookup{};
    static inline std::vector<std::string> sEnumValues{};

    static inline std::vector<std::string> sSoftEnums{};
    static inline EnumValues sSoftEnumLookup{};
    static inline std::vector<std::string> sSoftEnumValues{};
};

#endif // !COMMANDREGISTRY_HPP