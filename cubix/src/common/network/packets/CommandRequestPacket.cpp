#include "CommandRequestPacket.hpp"
void CommandRequestPacket::read(BinaryStream& stream)
{
    this->command = stream.readString<Endianness::NetworkEndian>();
    this->commandOrigin = BinaryStream::serialize<CommandOrigin>::read(stream);
    this->isInternalSource = stream.readBoolean();
    this->version = stream.readSignedVarInt();
};

void CommandRequestPacket::write(BinaryStream& stream)
{
    stream.writeString<Endianness::NetworkEndian>(this->command);
    BinaryStream::serialize<CommandOrigin>::write(this->commandOrigin, stream);
    stream.writeBoolean(this->isInternalSource);
    stream.writeSignedVarInt(this->version);
};