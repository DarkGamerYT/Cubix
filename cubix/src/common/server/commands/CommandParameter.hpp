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
    std::string mName;
    CommandParameterType mType;
    bool mIsOptional = false;
    uint64_t mSymbol = static_cast<uint64_t>(CommandSymbol::Epsilon);
    CommandParameterOption mOptions = CommandParameterOption::None;

public:
    explicit CommandParameter(const std::string& name, const CommandParameterType type = CommandParameterType::Basic)
        : mName(name), mType(type) {};

    const std::string& getName() const { return this->mName; };
    CommandParameterType getType() const { return this->mType; };

    bool isOptional() const { return this->mIsOptional; };
    CommandParameter& setOptional(const bool optional) { this->mIsOptional = optional; return *this; };

    uint64_t getSymbol() const { return this->mSymbol; };
    CommandParameter& setSymbol(const uint64_t symbol) { this->mSymbol = symbol; return *this; };
    CommandParameter& setSymbol(const CommandSymbol symbol) { return this->setSymbol(static_cast<uint64_t>(symbol)); };

    CommandParameterOption getOptions() const { return this->mOptions; };
    CommandParameter& addOption(CommandParameterOption option);
};

#endif // !COMMANDPARAMETER_HPP
