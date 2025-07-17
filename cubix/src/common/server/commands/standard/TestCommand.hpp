#pragma once
#include "../Command.hpp"

class TestCommand : public Command
{
public:
    explicit TestCommand(const CommandPermissionLevel permissionLevel)
        : Command("Testing command", permissionLevel) {};

    void setup() override;
    void execute(const CommandOrigin&/*, CommandOutput&*/) override;
};