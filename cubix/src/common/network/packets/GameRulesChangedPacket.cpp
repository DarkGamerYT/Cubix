#include "GameRulesChangedPacket.hpp"
void GameRulesChangedPacket::read(BinaryStream& stream)
{
    const uint32_t rulesSize = stream.readUnsignedVarInt();
    for (uint32_t i = 0; i < rulesSize; i++)
    {
        const std::string name = stream.readString<Endianness::NetworkEndian>();
        const bool canBeModifiedByPlayer = stream.readBoolean();

        switch (static_cast<GameRuleType>(stream.readUnsignedVarInt()))
        {
            case GameRuleType::Boolean: {
                GameRule gameRule{ name, stream.readBoolean(), canBeModifiedByPlayer };
                this->rules.emplace_back(gameRule.clone());
                break;
            };
            case GameRuleType::Integer: {
                GameRule gameRule{ name, static_cast<int>(stream.readUnsignedVarInt()), canBeModifiedByPlayer };
                this->rules.emplace_back(gameRule.clone());
                break;
            };
            case GameRuleType::Float: {
                GameRule gameRule{ name, stream.read<float>(), canBeModifiedByPlayer };
                this->rules.emplace_back(gameRule.clone());
                break;
            };
            default:
                break;
        };
    };
};

void GameRulesChangedPacket::write(BinaryStream& stream)
{
    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->rules.size()));
    for (const auto& rule : this->rules)
    {
        stream.writeString<Endianness::NetworkEndian>(rule->getName());
        stream.writeBoolean(rule->canBeModifiedByPlayer());

        GameRuleType ruleType = rule->getType();
        stream.writeUnsignedVarInt(static_cast<uint32_t>(ruleType));

        switch (ruleType)
        {
            case GameRuleType::Boolean: {
                const auto gameRule = dynamic_cast<const GameRule<bool>*>(rule.get());
                stream.writeBoolean(gameRule->getValue());
                break;
            };
            case GameRuleType::Integer: {
                const auto gameRule = dynamic_cast<const GameRule<int>*>(rule.get());
                stream.writeUnsignedVarInt(gameRule->getValue());
                break;
            };
            case GameRuleType::Float: {
                const auto gameRule = dynamic_cast<const GameRule<float>*>(rule.get());
                stream.write<float>(gameRule->getValue());
                break;
            };
            default:
                break;
        };
    };
};