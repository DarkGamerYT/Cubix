#include "CommandOutput.hpp"
bool CommandOutput::hasErrorMessage() const {
    for (const auto& outputMessage : this->mMessages)
        if (!outputMessage.isSuccessful)
        {
            return true;
        };

    return false;
};