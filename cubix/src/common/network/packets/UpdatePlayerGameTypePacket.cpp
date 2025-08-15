#include "UpdatePlayerGameTypePacket.hpp"
void UpdatePlayerGameTypePacket::read(BinaryStream& stream)
{
    this->gameType = static_cast<GameType>(stream.readSignedVarInt());
    this->playerActorUniqueId = stream.readSignedVarLong();
    this->tick = stream.readUnsignedVarLong();
};

void UpdatePlayerGameTypePacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(static_cast<int32_t>(this->gameType));
    stream.writeSignedVarLong(this->playerActorUniqueId);
    stream.writeUnsignedVarLong(this->tick);
};