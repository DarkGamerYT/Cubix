#ifndef GAMERULE_HPP
#define GAMERULE_HPP

#include <utility>
#include <variant>
#include <string>

#include "IGameRule.hpp"

template<typename T>
class GameRule final : public IGameRule {
private:
    T mValue;
    std::string mName;
    bool mShouldSave = true;
    bool mAllowUseInCommand = true;
    bool mRequiresCheats = true;
    bool mCanBeModifiedByPlayer = true;

public:
    explicit GameRule(std::string name, T value = false, const bool canBeModifiedByPlayer = true)
        : mValue(value), mName(std::move(name)), mCanBeModifiedByPlayer(canBeModifiedByPlayer) {};

    const std::string& getName() const override { return this->mName; };
    bool canBeModifiedByPlayer() const override { return this->mCanBeModifiedByPlayer; };

    GameRuleType getType() const override {
        if constexpr (std::is_same_v<T, bool>)
            return GameRuleType::Boolean;
        else if constexpr (std::is_same_v<T, int>)
            return GameRuleType::Integer;
        else if constexpr (std::is_same_v<T, float>)
            return GameRuleType::Float;

        else return GameRuleType::Invalid;
    };

    const T& getValue() const {
        return this->mValue;
    };

    GameRule& setValue(T value) {
        this->mValue = std::move(value);
        return *this;
    };

    std::unique_ptr<IGameRule> clone() const override {
        return std::make_unique<GameRule<T>>(this->getName(), this->getValue(), this->canBeModifiedByPlayer());
    };
};

#endif //GAMERULE_HPP
