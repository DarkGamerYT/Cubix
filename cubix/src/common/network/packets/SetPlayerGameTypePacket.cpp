#include "SetPlayerGameTypePacket.hpp"
void SetPlayerGameTypePacket::read(BinaryStream& stream)
{
    this->gameType = static_cast<GameType>(stream.readSignedVarInt());
};

void SetPlayerGameTypePacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(static_cast<int32_t>(this->gameType));
};