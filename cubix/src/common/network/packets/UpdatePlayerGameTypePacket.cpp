#include "UpdatePlayerGameTypePacket.hpp"
void UpdatePlayerGameTypePacket::read(BinaryStream& stream)
{
    this->gameType = static_cast<GameType>(stream.readSignedVarInt());
    this->playerActorId = stream.readSignedVarLong();
    this->tick = stream.readUnsignedVarLong();
};

void UpdatePlayerGameTypePacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(static_cast<int32_t>(this->gameType));
    stream.writeSignedVarLong(this->playerActorId);
    stream.writeUnsignedVarLong(this->tick);
};