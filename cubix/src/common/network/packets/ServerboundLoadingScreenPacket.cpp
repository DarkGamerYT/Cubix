#include "ServerboundLoadingScreenPacket.hpp"
void ServerboundLoadingScreenPacket::read(BinaryStream& stream)
{
    this->isEnd = stream.readSignedVarInt() == 2;

    bool hasValue = stream.readBoolean();
    if (true == hasValue)
        this->screenId = stream.readUnsignedInt();
};

void ServerboundLoadingScreenPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarInt(this->isEnd ? 2 : 1);

    stream.writeBoolean(screenId.has_value());
    if (screenId.has_value())
        stream.writeUnsignedInt(this->screenId.value());
};