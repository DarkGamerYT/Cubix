#ifndef COMMANDOUTPUTTYPE_HPP
#define COMMANDOUTPUTTYPE_HPP

enum class CommandOutputType : int {
    None       = 0,
    LastOutput = 1,
    Silent     = 2,
    AllOutput  = 3,
    DataSet    = 4
};

#endif // !COMMANDOUTPUTTYPE_HPP