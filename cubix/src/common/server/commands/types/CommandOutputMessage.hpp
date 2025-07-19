#ifndef COMMANDOUTPUTMESSAGE_HPP
#define COMMANDOUTPUTMESSAGE_HPP

#include <string>
#include <vector>

struct CommandOutputMessage
{
    bool isSuccessful;
    std::string message;
    std::vector<std::string> parameters;
};

#endif //COMMANDOUTPUTMESSAGE_HPP
