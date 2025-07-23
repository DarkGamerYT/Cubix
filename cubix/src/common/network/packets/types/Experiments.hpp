#ifndef EXPERIMENTS_HPP
#define EXPERIMENTS_HPP

#include <string>
#include <vector>

struct Experiment
{
    std::string toggleName;
    bool enabled;
};

struct Experiments
{
    std::vector<Experiment> list;
    bool experimentsEverEnabled;
};

#endif // !EXPERIMENTS_HPP