#include "CommandOrigin.hpp"
void CommandOrigin::writeNetwork(BinaryStream& stream) {
    stream.writeUnsignedVarInt(static_cast<uint32_t>(this->m_type));
    stream.writeUUID(this->m_uuid);
    stream.writeString<Endianness::NetworkEndian>(this->m_requestId);

    if (this->m_type == CommandOriginType::DevConsole || this->m_type == CommandOriginType::Test)
    {
        stream.writeSignedVarLong(this->m_playerId);
    };
};