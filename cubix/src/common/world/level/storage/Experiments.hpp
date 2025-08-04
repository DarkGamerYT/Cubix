#ifndef EXPERIMENTS_HPP
#define EXPERIMENTS_HPP

#include <unordered_map>
#include <string>

using ExperimentStorage = std::unordered_map<std::string, bool>;
struct Experiments
{
    ExperimentStorage experimentList;
    bool experimentsEverEnabled;
};

#endif //EXPERIMENTS_HPP
