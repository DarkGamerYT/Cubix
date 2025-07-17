#include "AvailableCommandsPacket.hpp"
void AvailableCommandsPacket::read(BinaryStream& stream)
{

};

void AvailableCommandsPacket::write(BinaryStream& stream)
{
    const std::vector<std::string>& enumValues = CommandRegistry::getAllEnumValues();
    { // Enum values
        stream.writeUnsignedVarInt(static_cast<uint32_t>(enumValues.size()));
        for (const std::string& value : enumValues)
        {
            stream.writeString(value);
        };
    };

    stream.writeUnsignedVarInt(0); // Chained Subcommands values

    { // Post fixes
        const std::vector<std::string>& postFixes = CommandRegistry::getPostFixes();

        stream.writeUnsignedVarInt(static_cast<uint32_t>(postFixes.size()));
        for (const std::string& value : postFixes)
        {
            stream.writeString(value);
        };
    };

    const auto& enums = CommandRegistry::getEnums();
    { // Enum data
        stream.writeUnsignedVarInt(static_cast<uint32_t>(enums.size()));

        for (const auto& name : enums)
        {
            stream.writeString(name);

            const auto& indexes = CommandRegistry::getEnumValues(name);
            const int size = indexes.size();
            stream.writeUnsignedVarInt(size);

            for (auto& index : indexes)
            {
                if (size <= sizeof(uint8_t))
                {
                    stream.writeByte(index);
                    continue;
                }
                else if (size <= sizeof(uint16_t))
                {
                    stream.writeUnsignedShort(index);
                    continue;
                };
                
                stream.writeUnsignedInt(index);
            };
        };
    };

    stream.writeUnsignedVarInt(0); // Chained Subcommands data

    this->writeCommands(stream); // Commands data

    const std::vector<std::string>& softEnumVales = CommandRegistry::getAllSoftEnumValues();
    const auto& softEnums = CommandRegistry::getSoftEnums();
    { // Soft Enums
        stream.writeUnsignedVarInt(static_cast<uint32_t>(softEnums.size()));
        for (const auto& name : softEnums)
        {
            const auto& indexes = CommandRegistry::getSoftEnumValues(name);
            stream.writeString(name);

            stream.writeUnsignedVarInt(static_cast<uint32_t>(indexes.size()));
            for (const uint64_t index : indexes)
            {
                stream.writeString(softEnumVales.at(index));
            };
        };
    };

    stream.writeUnsignedVarInt(0); // Constraints
};

void AvailableCommandsPacket::writeCommands(BinaryStream& stream)
{
    const auto& commands = CommandRegistry::getAll();

    stream.writeUnsignedVarInt(static_cast<uint32_t>(commands.size()));
    for (const auto& [name, command] : commands)
    {
        stream.writeString(name);
        stream.writeString(command->getDescription());
        stream.writeUnsignedShort(static_cast<uint16_t>(command->getFlags()));
        stream.writeByte(static_cast<uint8_t>(command->getPermissionLevel()));

        stream.writeInt(-1); // Aliases
        stream.writeUnsignedVarInt(0); // Chained Subcommands indexes

        const std::vector<CommandOverload>& overloads = command->getOverloads();

        stream.writeUnsignedVarInt(static_cast<uint32_t>(overloads.size()));
        for (const auto& overload : overloads)
        {
            stream.writeBoolean(overload.isChaining());
            this->writeParameters(stream, overload.getParameters());
        };
    };
};

void AvailableCommandsPacket::writeParameters(
    BinaryStream& stream,
    const std::vector<CommandParameter>& parameters
) {
    stream.writeUnsignedVarInt(static_cast<uint32_t>(parameters.size()));
    for (const CommandParameter& parameter : parameters)
    {
        unsigned int symbol = static_cast<int>(CommandSymbol::Epsilon);

        switch (parameter.getType())
        {
            case CommandParameterType::Enum:
            {
                symbol = static_cast<int>(CommandSymbolBit::EnumBit) | parameter.getSymbol();
                break;
            };
            case CommandParameterType::SoftEnum:
            {
                symbol = static_cast<int>(CommandSymbolBit::SoftEnumBit) | parameter.getSymbol();
                break;
            };
            case CommandParameterType::Postfix:
            {
                symbol = static_cast<int>(CommandSymbolBit::PostfixBit) | parameter.getSymbol();
                break;
            };
            case CommandParameterType::Basic:
            {
                symbol = parameter.getSymbol();
                break;
            };
            default:
                continue;
        };

        stream.writeString(parameter.getName());
        stream.writeUnsignedInt(symbol);
        stream.writeBoolean(parameter.isOptional());
        stream.writeByte(static_cast<uint8_t>(parameter.getOptions()));
    };
};