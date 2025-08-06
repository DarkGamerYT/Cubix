#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <vector>
#include <string>

#include "types/CommandPermissionLevel.hpp"
#include "CommandFlag.hpp"
#include "CommandOrigin.hpp"
#include "CommandOverload.hpp"
#include "CommandOutput.hpp"

class Command
{
private:
    std::string mDescription;
    CommandPermissionLevel mPermissionLevel;
    std::vector<CommandOverload> mOverloads = {};
    CommandFlag mFlags = CommandFlag::None;

public:
    virtual ~Command() = default;

    Command(
        const std::string& description,
        const CommandPermissionLevel permissionLevel
    ) : mDescription(description), mPermissionLevel(permissionLevel) {};

    virtual void setup() = 0;
    void run(const CommandOrigin&, CommandOutput&);
    virtual void execute(const CommandOrigin&, CommandOutput&) = 0;

    std::string getDescription() const { return this->mDescription; };
    CommandPermissionLevel getPermissionLevel() const { return this->mPermissionLevel; };

    const std::vector<CommandOverload>& getOverloads() const { return this->mOverloads; };
    void addOverload(const CommandOverload& overload) { this->mOverloads.emplace_back(overload); };

    CommandFlag getFlags() const { return this->mFlags; };
    void addFlag(CommandFlag flag);
    bool hasFlag(CommandFlag flag) const;
};

#endif // !COMMAND_HPP