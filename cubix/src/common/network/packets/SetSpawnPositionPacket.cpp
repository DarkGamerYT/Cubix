#include "SetSpawnPositionPacket.hpp"

void SetSpawnPositionPacket::read(BinaryStream& stream)
{
    this->spawnPositionType = static_cast<SpawnPositionType>(stream.readSignedVarInt());
    this->blockPosition = stream.readBlockPosition<Endianness::NetworkEndian>();
    this->dimension = stream.readSignedVarInt();
    this->spawnBlockPosition = stream.readBlockPosition<Endianness::NetworkEndian>();
};

void SetSpawnPositionPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(static_cast<int32_t>(this->spawnPositionType));
    stream.writeBlockPosition<Endianness::NetworkEndian>(this->blockPosition);
    stream.writeSignedVarInt(this->dimension);
    stream.writeBlockPosition<Endianness::NetworkEndian>(this->spawnBlockPosition);
};