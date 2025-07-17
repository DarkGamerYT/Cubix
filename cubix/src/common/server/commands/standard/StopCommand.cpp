#include "StopCommand.hpp"

#include "../../ServerInstance.hpp"
#include "../../../registry/CommandRegistry.hpp"

void StopCommand::setup() {};

void StopCommand::execute(const CommandOrigin& origin/*, CommandOutput&*/) {
    Logger::log(Logger::LogLevel::Info, "Server stop requested.");

    const auto& serverInstance = origin.getServerInstance();
    serverInstance->shutdown();
};