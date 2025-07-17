#ifndef COMMANDPARAMETER_HPP
#define COMMANDPARAMETER_HPP
#include <string>
#include <utility>

#include "types/CommandParameterType.hpp"
#include "types/CommandParameterOption.hpp"
#include "types/CommandSymbol.hpp"

class CommandParameter
{
private:
    std::string m_Name;
    CommandParameterType m_Type;
    bool m_IsOptional = false;
    uint64_t m_Symbol = static_cast<uint64_t>(CommandSymbol::Epsilon);
    CommandParameterOption m_Options = CommandParameterOption::None;

public:
    explicit CommandParameter(const std::string& name, const CommandParameterType type = CommandParameterType::Basic)
        : m_Name(name), m_Type(type) {};

    const std::string& getName() const { return this->m_Name; };
    CommandParameterType getType() const { return this->m_Type; };

    bool isOptional() const { return this->m_IsOptional; };
    CommandParameter& setOptional(const bool optional) { this->m_IsOptional = optional; return *this; };

    uint64_t getSymbol() const { return this->m_Symbol; };
    CommandParameter& setSymbol(const uint64_t symbol) { this->m_Symbol = symbol; return *this; };
    CommandParameter& setSymbol(const CommandSymbol symbol) { return this->setSymbol(static_cast<uint64_t>(symbol)); };

    CommandParameterOption getOptions() const { return this->m_Options; };
    CommandParameter& addOption(CommandParameterOption option);
};

#endif // !COMMANDPARAMETER_HPP
