#ifndef COMMANDPARAMETEROPTION_HPP
#define COMMANDPARAMETEROPTION_HPP

#include <cstdint>

enum class CommandParameterOption : uint8_t {
    None                      = 0,
    EnumAutocompleteExpansion = 1 << 0,
    HasSemanticConstraint     = 1 << 1,
    EnumAsChainedCommand      = 1 << 2
};

#endif // !COMMANDPARAMETEROPTION_HPP