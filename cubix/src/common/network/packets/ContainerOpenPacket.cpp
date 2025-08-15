#include "ContainerOpenPacket.hpp"
void ContainerOpenPacket::read(BinaryStream& stream)
{
    this->containerId = stream.readByte();
    this->containerType = static_cast<ContainerType>(stream.readByte());
    this->position = stream.readBlockPosition<Endianness::NetworkEndian>();
    this->actorUniqueId = BinaryStream::serialize<ActorUniqueId>::read(stream);
};

void ContainerOpenPacket::write(BinaryStream& stream)
{
    stream.writeByte(this->containerId);
    stream.writeByte(static_cast<uint8_t>(this->containerType));
    stream.writeBlockPosition<Endianness::NetworkEndian>(this->position);
    BinaryStream::serialize<ActorUniqueId>::write(this->actorUniqueId, stream);
};