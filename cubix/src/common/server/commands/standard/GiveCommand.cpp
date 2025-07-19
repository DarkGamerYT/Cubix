#include "GiveCommand.hpp"

#include "../../../registry/CommandRegistry.hpp"

void GiveCommand::setup()
{
    this->addOverload(CommandOverload{ true,
        CommandParameter{ "player" }
            .setSymbol(CommandSymbol::Selection),

        CommandParameter{ "itemName", CommandParameterType::Enum }
            .setSymbol(CommandRegistry::getEnum("Item")),

        CommandParameter{ "amount" }
            .setSymbol(CommandSymbol::Int)
            .setOptional(true),

        CommandParameter{ "data" }
            .setSymbol(CommandSymbol::Int)
            .setOptional(true),
        
        CommandParameter{ "components" }
            .setSymbol(CommandSymbol::JsonObject)
            .setOptional(true)
    });
};

void GiveCommand::execute(const CommandOrigin& origin, CommandOutput& output) {
    output.success("GiveCommand::execute() - Hello, world!");
};