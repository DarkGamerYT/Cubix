#include "RequestNetworkSettingsPacket.hpp"
#include "../../SharedConstants.hpp"

void RequestNetworkSettingsPacket::read(BinaryStream& stream)
{
    this->protocol = stream.readUnsignedInt<Endianness::BigEndian>();
};

void RequestNetworkSettingsPacket::write(BinaryStream& stream)
{
    stream.writeUnsignedInt<Endianness::BigEndian>(this->protocol);
};