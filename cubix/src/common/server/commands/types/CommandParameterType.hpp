#pragma once
enum class CommandParameterType : int {
    Basic             = 0,
    Enum              = 1,
    SoftEnum          = 2,
    Postfix           = 3,
    ChainedSubcommand = 4
};