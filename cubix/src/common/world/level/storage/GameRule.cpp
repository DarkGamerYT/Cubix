#include "GameRule.hpp"
GameRuleType GameRule::getType() const {
    return std::visit([]<typename T0>(const T0& value) -> GameRuleType {
        using T = std::decay_t<T0>;
        if constexpr (std::is_same_v<T, bool>)  return GameRuleType::Boolean;
        if constexpr (std::is_same_v<T, int>)   return GameRuleType::Integer;
        if constexpr (std::is_same_v<T, float>) return GameRuleType::Float;

        return GameRuleType::Invalid;
    }, this->mValue);
};