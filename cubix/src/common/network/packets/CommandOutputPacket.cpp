#include "CommandOutputPacket.hpp"
void CommandOutputPacket::read(BinaryStream& stream)
{
    {
        // Command origin stuff
        const auto type = static_cast<CommandOriginType>(stream.readUnsignedVarInt());
        const Util::UUID& commandUUID = stream.readUUID();
        const std::string& requestId = stream.readString();

        this->commandOrigin = std::make_unique<CommandOrigin>(type, nullptr, commandUUID, requestId);
        if (type == CommandOriginType::DevConsole || type == CommandOriginType::Test)
        {
            this->commandOrigin->setPlayerId(stream.readSignedVarLong());
        };
    };

    // TODO: Read command output
};

void CommandOutputPacket::write(BinaryStream& stream)
{
    this->commandOrigin->writeNetwork(stream);

    stream.writeByte(static_cast<uint8_t>(this->commandOutput.getType()));
    stream.writeUnsignedVarInt(this->commandOutput.getSuccessCount());

    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->commandOutput.getMessages().size()));
    for (const auto& [isSuccessful, message, parameters] : this->commandOutput.getMessages())
    {
        stream.writeBoolean(isSuccessful);
        stream.writeString(message);

        stream.writeUnsignedVarInt(static_cast<uint32_t>(parameters.size()));
        for (const std::string& parameter : parameters)
        {
            stream.writeString(parameter);
        };
    };

    if (this->commandOutput.getType() == CommandOutputType::DataSet)
    {
        stream.writeString(this->commandOutput.getData());
    };
};