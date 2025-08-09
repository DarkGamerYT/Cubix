#ifndef BLOCKSTATE_HPP
#define BLOCKSTATE_HPP

#include <unordered_map>
#include <string>
#include <variant>
#include <vector>
#include <iostream>

typedef std::variant<std::string, int, bool> StateType;
class BlockState
{
private:
    std::string mIdentifier;
    std::vector<StateType> mPossibleStates;
    StateType mValue;

public:
    BlockState() : mValue(0) {};
    BlockState(const std::string& identifier, const std::vector<StateType>& possibleStates)
        : mIdentifier(identifier), mPossibleStates(possibleStates),
        mValue(!possibleStates.empty() ? possibleStates.at(0) : 0) {};

    const std::string& identifier() const { return this->mIdentifier; };
    int type() const { return this->mValue.index(); };

    const std::vector<StateType>& getPossibleStates() const { return this->mPossibleStates; };
    void setPossibleStates(const std::vector<StateType>& states) { this->mPossibleStates = states; };

    StateType getValue() const { return this->mValue; };
    BlockState& setValue(const StateType& value)
    {
        if (value.index() != mValue.index())
        {

            return *this;
        };

        this->mValue = value;
        return *this;
    };
};

#endif // !BLOCKSTATE_HPP
