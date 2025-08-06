#ifndef COMMANDOUTPUT_HPP
#define COMMANDOUTPUT_HPP

#include <string>

#include "types/CommandOutputType.hpp"
#include "types/CommandOutputMessage.hpp"

class CommandOutput {
private:
    CommandOutputType mType;
    uint32_t mSuccessCount = 0;
    std::string mData;
    std::vector<CommandOutputMessage> mMessages;

public:
    explicit CommandOutput(const CommandOutputType type = CommandOutputType::None)
        : mType(type) {};

    CommandOutputType getType() const { return this->mType; };
    uint32_t getSuccessCount() const { return this->mSuccessCount; };

    std::string getData() const { return this->mData; };
    bool wantsData() const { return this->mType == CommandOutputType::DataSet; };

    const std::vector<CommandOutputMessage>& getMessages() const { return this->mMessages; };

    bool hasErrorMessage() const;
    void addMessage(
        const std::string& message,
        const std::vector<std::string>& parameters = {},
        const bool hasError = false
    ) {
        this->mMessages.emplace_back(!hasError, message, parameters);
    };

    void error(const std::string& message, const std::vector<std::string>& parameters = {})
    {
        this->addMessage(message, parameters, true);
    };
    void success(const std::string& message, const std::vector<std::string>& parameters = {})
    {
        this->addMessage(message, parameters);
    };
};

#endif //COMMANDOUTPUT_HPP
