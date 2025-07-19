#include "TestCommand.hpp"

#include "../../../registry/CommandRegistry.hpp"

void TestCommand::setup()
{
    this->addFlag(CommandFlag::NotCheat);
    this->addFlag(CommandFlag::TestUsage);

    this->addOverload(CommandOverload{ true,
        CommandParameter{ "one", CommandParameterType::Enum }
            .setSymbol(CommandRegistry::addEnum("test", { "a" })),

        CommandParameter{ "two", CommandParameterType::Enum }
            .setSymbol(CommandRegistry::addEnum("hello", { "hello" }))
    });

    this->addOverload(CommandOverload{ true,
        CommandParameter{ "one", CommandParameterType::Enum }
            .setSymbol(CommandRegistry::addEnum("b", { "b" })),

        CommandParameter{ "name", CommandParameterType::Enum }
            .setSymbol(CommandRegistry::getEnum("Item"))
            .setOptional(true)
    });
};

void TestCommand::execute(const CommandOrigin& origin, CommandOutput& output) {
    output.success("TestCommand::execute() - Hello, world!");
};