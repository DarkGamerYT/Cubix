#include "CommandOrigin.hpp"
BinaryStream::serialize<CommandOrigin>::readType
BinaryStream::serialize<CommandOrigin>::read(BinaryStream& stream) {
    const auto type = static_cast<CommandOriginType>(stream.readUnsignedVarInt());
    const Util::UUID& commandUUID = stream.readUUID();
    const std::string& requestId = stream.readString<Endianness::NetworkEndian>();

    ActorUniqueId uniqueId{ -1 };
    if (type == CommandOriginType::DevConsole || type == CommandOriginType::Test)
        uniqueId = BinaryStream::serialize<ActorUniqueId>::read(stream);

    return std::make_unique<CommandOrigin>(type, nullptr, commandUUID, requestId, uniqueId);
};

void BinaryStream::serialize<CommandOrigin>::write(writeType value, BinaryStream& stream) {
    stream.writeUnsignedVarInt(static_cast<uint32_t>(value->mType));
    stream.writeUUID(value->mUUID);
    stream.writeString<Endianness::NetworkEndian>(value->mRequestId);

    if (value->mType == CommandOriginType::DevConsole || value->mType == CommandOriginType::Test)
        BinaryStream::serialize<ActorUniqueId>::write(value->mPlayerId, stream);
};