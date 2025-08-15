#include "CommandOutput.hpp"
bool CommandOutput::hasErrorMessage() const {
    for (const auto& outputMessage : this->mMessages)
        if (!outputMessage.isSuccessful) {
            return true;
        };

    return false;
};

void CommandOutput::error(const std::string& message, const std::vector<std::string>& parameters)
{
    mMessages.emplace_back(false, message, parameters);
};
void CommandOutput::success(const std::string& message, const std::vector<std::string>& parameters)
{
    mMessages.emplace_back(true, message, parameters);
    mSuccessCount++;
};