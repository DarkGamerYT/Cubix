#pragma once
#include "../Command.hpp"

class StopCommand : public Command
{
public:
    explicit StopCommand(const CommandPermissionLevel permissionLevel)
        : Command("commands.stop.description", permissionLevel) {};

    void setup() override;
    void execute(const CommandOrigin&, CommandOutput&) override;
};