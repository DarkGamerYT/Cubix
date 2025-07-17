#include "SetCommandsEnabledPacket.hpp"
void SetCommandsEnabledPacket::read(BinaryStream& stream)
{
    this->commandsEnabled = stream.readBoolean();
};

void SetCommandsEnabledPacket::write(BinaryStream& stream)
{
    stream.writeBoolean(this->commandsEnabled);
};