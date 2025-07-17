#include "ClientCacheStatusPacket.hpp"
void ClientCacheStatusPacket::read(BinaryStream& stream)
{
    this->isCacheSupported = stream.readBoolean();
};

void ClientCacheStatusPacket::write(BinaryStream& stream)
{
    stream.writeBoolean(this->isCacheSupported);
};