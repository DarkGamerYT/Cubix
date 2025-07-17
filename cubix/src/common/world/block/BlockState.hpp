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
    std::string m_Identifier;
    std::vector<StateType> m_PossibleStates;
    StateType m_Value;

public:
    BlockState() : m_Value(0) {};
    BlockState(const std::string& identifier, const std::vector<StateType>& possibleStates)
        : m_Identifier(identifier), m_PossibleStates(possibleStates),
        m_Value(!possibleStates.empty() ? possibleStates.at(0) : 0) {};

    std::string identifier() const { return this->m_Identifier; };
    int type() const { return this->m_Value.index(); };

    std::vector<StateType> getPossibleStates() const { return this->m_PossibleStates; };
    void setPossibleStates(const std::vector<StateType>& states) { this->m_PossibleStates = states; };

    StateType getValue() const { return this->m_Value; };
    BlockState& setValue(const StateType& value)
    {
        if (value.index() != m_Value.index())
        {

            return *this;
        };

        this->m_Value = value;
        return *this;
    };
};

#endif // !BLOCKSTATE_HPP
