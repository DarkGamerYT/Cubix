#include "BlockStateRegistry.hpp"
void BlockStateRegistry::initialize()
{
    sStates.emplace_back(ACTIVE);
    sStates.emplace_back(AGE);
    sStates.emplace_back(AGE_BIT);
    {
        std::vector<StateType> stackBits;
        for (int i = 0; i < 64; i++)
            stackBits.emplace_back(i);
        BOOKS_STORED.setPossibleStates(stackBits);
    };
    sStates.emplace_back(BOOKS_STORED);


    {
        std::vector<StateType> vinesAge;
        for (int i = 0; i < 26; i++)
            vinesAge.emplace_back(i);
        TWISTING_VINES_AGE.setPossibleStates(vinesAge);
        WEEPING_VINES_AGE.setPossibleStates(vinesAge);
    };
    sStates.emplace_back(TWISTING_VINES_AGE);
    sStates.emplace_back(WEEPING_VINES_AGE);

    sStates.emplace_back(PILLAR_AXIS);
};