#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <vector>
#include <string>

#include "CommandPermissionLevel.hpp"
#include "CommandFlag.hpp"
#include "CommandOrigin.hpp"
#include "CommandOverload.hpp"

class Command
{
private:
    std::string m_Description;
    CommandPermissionLevel m_PermissionLevel;
    std::vector<CommandOverload> m_Overloads = {};
    CommandFlag m_Flags = CommandFlag::None;

public:
    virtual ~Command() = default;

    Command(
        const std::string& description,
        const CommandPermissionLevel permissionLevel
    ) : m_Description(description), m_PermissionLevel(permissionLevel) {};

    virtual void setup() = 0;
    void run(const CommandOrigin&/*, CommandOutput&*/);
    virtual void execute(const CommandOrigin&/*, CommandOutput&*/) = 0;

    std::string getDescription() const { return this->m_Description; };
    CommandPermissionLevel getPermissionLevel() const { return this->m_PermissionLevel; };

    const std::vector<CommandOverload>& getOverloads() const { return this->m_Overloads; };
    void addOverload(const CommandOverload& overload) { this->m_Overloads.emplace_back(overload); };

    CommandFlag getFlags() const { return this->m_Flags; };
    void addFlag(CommandFlag flag);
    bool hasFlag(CommandFlag flag) const;
};

#endif // !COMMAND_HPP