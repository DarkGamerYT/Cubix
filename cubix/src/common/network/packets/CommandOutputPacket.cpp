#include "CommandOutputPacket.hpp"
void CommandOutputPacket::read(BinaryStream& stream)
{
    this->commandOrigin = BinaryStream::serialize<CommandOrigin>::read(stream);

    const auto type = static_cast<CommandOutputType>(stream.readByte());
    this->commandOutput = CommandOutput{ type };

    stream.readUnsignedVarInt(); // Success count

    const uint32_t size = stream.readUnsignedVarInt();
    for (uint32_t i = 0; i < size; i++)
    {
        const bool isSuccessful = stream.readBoolean();
        const auto& message = stream.readString<Endianness::NetworkEndian>();

        std::vector<std::string> parameters;

        const uint32_t parameterSize = stream.readUnsignedVarInt();
        for (uint32_t j = 0; j < parameterSize; j++)
            parameters.emplace_back(stream.readString<Endianness::NetworkEndian>());

        if (isSuccessful)
            this->commandOutput.success(message, parameters);
        else
            this->commandOutput.error(message, parameters);
    };

    if (this->commandOutput.wantsData())
        stream.readString<Endianness::NetworkEndian>();
};

void CommandOutputPacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<CommandOrigin>::write(this->commandOrigin, stream);

    stream.writeByte(static_cast<uint8_t>(this->commandOutput.getType()));
    stream.writeUnsignedVarInt(this->commandOutput.getSuccessCount());

    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->commandOutput.getMessages().size()));
    for (const auto& [isSuccessful, message, parameters] : this->commandOutput.getMessages())
    {
        stream.writeBoolean(isSuccessful);
        stream.writeString<Endianness::NetworkEndian>(message);

        stream.writeUnsignedVarInt(static_cast<uint32_t>(parameters.size()));
        for (const std::string& parameter : parameters)
            stream.writeString<Endianness::NetworkEndian>(parameter);
    };

    if (this->commandOutput.wantsData())
        stream.writeString<Endianness::NetworkEndian>(this->commandOutput.getData());
};