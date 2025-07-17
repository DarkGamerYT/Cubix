#include "PlayStatusPacket.hpp"
void PlayStatusPacket::read(BinaryStream& stream)
{
    this->status = static_cast<PlayStatus>(stream.readUnsignedInt<Endianness::BigEndian>());
};

void PlayStatusPacket::write(BinaryStream& stream)
{
    stream.writeUnsignedInt<Endianness::BigEndian>(static_cast<uint32_t>(this->status));
};