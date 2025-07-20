#include "ShowStoreOfferPacket.hpp"
void ShowStoreOfferPacket::read(BinaryStream& stream)
{
    this->productId = stream.readString<Endianness::NetworkEndian>();
    this->redirectType = static_cast<RedirectType>(stream.readByte());
};

void ShowStoreOfferPacket::write(BinaryStream& stream)
{
    stream.writeString<Endianness::NetworkEndian>(this->productId);
    stream.writeByte(static_cast<uint8_t>(this->redirectType));
};