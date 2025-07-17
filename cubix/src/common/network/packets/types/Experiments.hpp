#pragma once
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