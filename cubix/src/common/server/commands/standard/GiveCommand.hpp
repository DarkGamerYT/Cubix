#pragma once
#include "../Command.hpp"

class GiveCommand final : public Command
{
public:
    explicit GiveCommand(const CommandPermissionLevel permissionLevel)
        : Command("commands.give.description", permissionLevel) {};

    void setup() override;
    void execute(const CommandOrigin&, CommandOutput&) override;
};