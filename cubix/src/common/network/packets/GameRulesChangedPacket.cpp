#include "GameRulesChangedPacket.hpp"
void GameRulesChangedPacket::read(BinaryStream& stream)
{
    const uint32_t rulesSize = stream.readUnsignedVarInt();
    for (uint32_t i = 0; i < rulesSize; i++)
    {
        const std::string name = stream.readString<Endianness::NetworkEndian>();
        const bool canBeModifiedByPlayer = stream.readBoolean();

        GameRule gameRule{ name, canBeModifiedByPlayer };

        switch (static_cast<GameRuleType>(stream.readUnsignedVarInt()))
        {
            case GameRuleType::Boolean: {
                const bool value = stream.readBoolean();
                gameRule.setValue(value);
                break;
            };
            case GameRuleType::Integer: {
                const int value = stream.readUnsignedVarInt();
                gameRule.setValue(value);
                break;
            };
            case GameRuleType::Float: {
                const float value = stream.readUnsignedInt();
                gameRule.setValue(value);
                break;
            };
            default:
                break;
        };

        this->rules.emplace_back(gameRule);
    };
};

void GameRulesChangedPacket::write(BinaryStream& stream)
{
    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->rules.size()));
    for (const GameRule& rule : this->rules)
    {
        stream.writeString<Endianness::NetworkEndian>(rule.getName());
        stream.writeBoolean(rule.canBeModifiedByPlayer());

        GameRuleType ruleType = rule.getType();
        stream.writeUnsignedVarInt(static_cast<uint32_t>(ruleType));

        switch (ruleType)
        {
            case GameRuleType::Boolean:
                stream.writeBoolean(rule.getValue<bool>()); break;
            case GameRuleType::Integer:
                stream.writeUnsignedVarInt(rule.getValue<int>()); break;
            case GameRuleType::Float:
                stream.writeUnsignedInt(static_cast<uint32_t>(rule.getValue<float>())); break;
            default:
                break;
        };
    };
};