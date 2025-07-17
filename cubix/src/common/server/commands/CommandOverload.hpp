#ifndef COMMANDOVERLOAD_HPP
#define COMMANDOVERLOAD_HPP

#include <vector>

#include "CommandParameter.hpp"

template<typename T>
concept IsCommandParameter = std::is_same_v<std::decay_t<T>, CommandParameter>;

class CommandOverload {
private:
    bool m_isChaining = false;
    std::vector<CommandParameter> m_parameters{};

public:
    template <typename... Args>
    requires (IsCommandParameter<Args> && ...)
    explicit CommandOverload(const bool isChaining, Args&&... args) : m_isChaining(isChaining) {
        m_parameters.reserve(sizeof...(Args));
        (m_parameters.emplace_back(std::forward<Args>(args)), ...);
    };

    bool isChaining() const { return this->m_isChaining; };
    const std::vector<CommandParameter>& getParameters() const { return this->m_parameters; };
};

#endif //COMMANDOVERLOAD_HPP
