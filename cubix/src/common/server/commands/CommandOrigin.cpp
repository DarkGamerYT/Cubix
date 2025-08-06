#include "CommandOrigin.hpp"
void CommandOrigin::writeNetwork(BinaryStream& stream) {
    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->mType));
    stream.writeUUID(this->mUuid);
    stream.writeString<Endianness::NetworkEndian>(this->mRequestId);

    if (this->mType == CommandOriginType::DevConsole || this->mType == CommandOriginType::Test)
    {
        stream.writeSignedVarLong(this->mPlayerId);
    };
};