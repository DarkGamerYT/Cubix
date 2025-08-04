#ifndef GAMERULE_HPP
#define GAMERULE_HPP

#include <variant>
#include <string>

enum class GameRuleType {
    Invalid = 0,
    Boolean = 1,
    Integer = 2,
    Float   = 3
};

class GameRule {
private:
    std::variant<bool, int, float> mValue;
    std::string mName;
    bool mShouldSave = true;
    bool mAllowUseInCommand = true;
    bool mRequiresCheats = true;
    bool mCanBeModifiedByPlayer = true;

public:
    explicit GameRule(const std::string& name, const bool canBeModifiedByPlayer = true)
        : mName(name), mCanBeModifiedByPlayer(canBeModifiedByPlayer) {};

    const std::string& getName() const { return this->mName; };
    GameRuleType getType() const;
    bool canBeModifiedByPlayer() const { return this->mCanBeModifiedByPlayer; };

    template<typename T>
    const T& getValue() const {
        return std::get<T>(this->mValue);
    };

    template<typename T>
    GameRule& setValue(T value) {
        this->mValue = std::move(value);
        return *this;
    };
};

#endif //GAMERULE_HPP
