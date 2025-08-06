#ifndef IGAMERULE_HPP
#define IGAMERULE_HPP

#include <memory>

enum class GameRuleType {
    Invalid = 0,
    Boolean = 1,
    Integer = 2,
    Float   = 3
};

class IGameRule {
public:
    virtual ~IGameRule() = default;

    virtual const std::string& getName() const = 0;
    virtual bool canBeModifiedByPlayer() const = 0;

    virtual GameRuleType getType() const = 0;
    virtual std::unique_ptr<IGameRule> clone() const = 0;
};

#endif //IGAMERULE_HPP
