#ifndef COMMANDPARAMETERTYPE_HPP
#define COMMANDPARAMETERTYPE_HPP

enum class CommandParameterType : int {
    Basic             = 0,
    Enum              = 1,
    SoftEnum          = 2,
    Postfix           = 3,
    ChainedSubcommand = 4
};

#endif // !COMMANDPARAMETERTYPE_HPP