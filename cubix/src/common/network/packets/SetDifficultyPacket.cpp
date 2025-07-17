#include "SetDifficultyPacket.hpp"
void SetDifficultyPacket::read(BinaryStream& stream)
{
    this->difficulty = (Difficulty)stream.readUnsignedVarInt();
};

void SetDifficultyPacket::write(BinaryStream& stream)
{
    stream.writeUnsignedVarInt((uint32_t)this->difficulty);
};