#include "CommandOutput.hpp"
bool CommandOutput::hasErrorMessage() const {
    for (const auto& outputMessage : this->m_messages)
        if (!outputMessage.isSuccessful)
        {
            return true;
        };

    return false;
};