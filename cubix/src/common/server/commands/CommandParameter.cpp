#include "CommandParameter.hpp"
CommandParameter& CommandParameter::addOption(CommandParameterOption option) {
    using T = std::underlying_type_t<CommandParameterOption>;
    this->m_Options = static_cast<CommandParameterOption>(
        static_cast<T>(option) | static_cast<T>(this->m_Options));
    return *this;
};