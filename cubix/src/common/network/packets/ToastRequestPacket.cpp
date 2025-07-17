#include "ToastRequestPacket.hpp"
void ToastRequestPacket::read(BinaryStream& stream)
{
    this->title = stream.readString();
    this->content = stream.readString();
};

void ToastRequestPacket::write(BinaryStream& stream)
{
    stream.writeString(this->title);
    stream.writeString(this->content);
};