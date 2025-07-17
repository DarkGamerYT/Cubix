#include "EditorNetworkPacket.hpp"
void EditorNetworkPacket::read(BinaryStream& stream)
{
    
};

void EditorNetworkPacket::write(BinaryStream& stream)
{
    stream.writeByte(this->routeToManager);
    Nbt::write<Endianness::NetworkEndian>(stream, this->payload.copy());
};