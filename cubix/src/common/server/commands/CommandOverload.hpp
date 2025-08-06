#ifndef COMMANDOVERLOAD_HPP
#define COMMANDOVERLOAD_HPP

#include <vector>

#include "CommandParameter.hpp"

template<typename T>
concept IsCommandParameter = std::is_same_v<std::decay_t<T>, CommandParameter>;

class CommandOverload {
private:
    bool mIsChaining = false;
    std::vector<CommandParameter> mParameters{};

public:
    template <typename... Args>
    requires (IsCommandParameter<Args> && ...)
    explicit CommandOverload(const bool isChaining, Args&&... args) : mIsChaining(isChaining) {
        mParameters.reserve(sizeof...(Args));
        (mParameters.emplace_back(std::forward<Args>(args)), ...);
    };

    bool isChaining() const { return this->mIsChaining; };
    const std::vector<CommandParameter>& getParameters() const { return this->mParameters; };
};

#endif //COMMANDOVERLOAD_HPP
