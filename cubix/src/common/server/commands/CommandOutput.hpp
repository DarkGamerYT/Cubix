#ifndef COMMANDOUTPUT_HPP
#define COMMANDOUTPUT_HPP

#include <string>

#include "types/CommandOutputType.hpp"
#include "types/CommandOutputMessage.hpp"

class CommandOutput {
private:
    CommandOutputType m_type;
    uint32_t m_successCount = 0;
    std::string m_data;
    std::vector<CommandOutputMessage> m_messages;

public:
    explicit CommandOutput(const CommandOutputType type = CommandOutputType::None)
        : m_type(type) {};

    CommandOutputType getType() const { return this->m_type; };
    uint32_t getSuccessCount() const { return this->m_successCount; };

    std::string getData() const { return this->m_data; };
    bool wantsData() const { return this->m_type == CommandOutputType::DataSet; };

    const std::vector<CommandOutputMessage>& getMessages() const { return this->m_messages; };

    bool hasErrorMessage() const;
    void addMessage(
        const std::string& message,
        const std::vector<std::string>& parameters = {},
        const bool hasError = false
    ) {
        this->m_messages.emplace_back(!hasError, message, parameters);
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
