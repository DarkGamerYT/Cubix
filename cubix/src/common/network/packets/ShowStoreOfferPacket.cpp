#include "ShowStoreOfferPacket.hpp"
void ShowStoreOfferPacket::read(BinaryStream& stream)
{
    this->productId = stream.readString();
    this->redirectType = (RedirectType)stream.readByte();
};

void ShowStoreOfferPacket::write(BinaryStream& stream)
{
    stream.writeString(this->productId);
    stream.writeByte((uint8_t)this->redirectType);
};