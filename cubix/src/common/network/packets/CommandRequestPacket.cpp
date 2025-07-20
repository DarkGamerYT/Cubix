#include "CommandRequestPacket.hpp"
void CommandRequestPacket::read(BinaryStream& stream)
{
    this->command = stream.readString<Endianness::NetworkEndian>();
    {
        // Command origin stuff
        const auto type = static_cast<CommandOriginType>(stream.readUnsignedVarInt());
        const Util::UUID& commandUUID = stream.readUUID();
        const std::string& requestId = stream.readString<Endianness::NetworkEndian>();

        this->commandOrigin = std::make_unique<CommandOrigin>(type, nullptr, commandUUID, requestId);
        if (type == CommandOriginType::DevConsole || type == CommandOriginType::Test)
        {
            this->commandOrigin->setPlayerId(stream.readSignedVarLong());
        };
    };
    this->isInternalSource = stream.readBoolean();
    this->version = stream.readSignedVarInt();
};

void CommandRequestPacket::write(BinaryStream& stream)
{
    stream.writeString<Endianness::NetworkEndian>(this->command);
    this->commandOrigin->writeNetwork(stream);
    stream.writeBoolean(this->isInternalSource);
    stream.writeSignedVarInt(this->version);
};