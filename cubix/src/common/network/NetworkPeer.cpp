#include "NetworkPeer.hpp"
#include "NetworkServer.hpp"
BinaryStream& NetworkPeer::receivePacket(BinaryStream& stream)
{
    if (this->isCompressed())
    {
        stream.readByte();
    };

    switch (this->m_Compression)
    {
        case CompressionType::Zlib:
        {
            const uint32_t compressedSize = stream.readUnsignedVarInt();
            const uint8_t* compressedData = stream.readBytes(compressedSize);

            BinaryStream binaryStream{};
            if (compressedSize < this->m_CompressionThreshold) {
                binaryStream.writeUnsignedVarInt(compressedSize);
                binaryStream.writeBytes(compressedData, compressedSize);

                stream = binaryStream;
                break;
            };

            constexpr uLongf maxDecompressedSize = 2 * 1024 * 1024;
            std::vector<uint8_t> decompressedBuffer(maxDecompressedSize);
            uLongf decompressedSize = maxDecompressedSize;

            const int result = uncompress(
                decompressedBuffer.data(), &decompressedSize,
                compressedData, compressedSize
            );

            if (result != Z_OK) {
                stream = binaryStream;
                break;
            };

            binaryStream.writeUnsignedVarInt(decompressedSize);
            binaryStream.writeBytes(decompressedBuffer.data(), decompressedSize);
            stream = binaryStream;
            break;
        };
        case CompressionType::Snappy:
        {

            break;
        };
        default:
            break;
    };

    return stream;
};

void NetworkPeer::sendPacket(Packet& packet, SubClientId subClientId, NetworkPeer::Reliability reliability)
{
    BinaryStream packetStream;
    packetStream.writeByte(0xFE);

    if (this->isCompressed())
        packetStream.writeByte(static_cast<uint8_t>(this->m_Compression));

    BinaryStream dataStream;

    {
        uint16_t packetHeader = 0;
        const auto packetId = static_cast<uint16_t>(packet.getId());
        const uint8_t subClientSenderId = 0;
        const auto subClientTargetId = static_cast<uint8_t>(subClientId);

        // First 10 bits: Packet ID
        packetHeader |= (packetId & 0x03FF); // 0x03FF == 0b0000001111111111

        // Next 2 bits: Sender SubClient ID (bits 10-11)
        packetHeader |= (static_cast<uint16_t>(subClientSenderId & 0x03) << 10);

        // Next 2 bits: Target SubClient ID (bits 12-13)
        packetHeader |= (static_cast<uint16_t>(subClientTargetId & 0x03) << 12);

        dataStream.writeUnsignedVarInt(packetHeader);
    };

    packet.write(dataStream);

    const size_t rawSize = dataStream.size();
    switch (this->m_Compression)
    {
        case CompressionType::Disabled:
        case CompressionType::None:
        {
            // Write both game packet data and header size
            packetStream.writeUnsignedVarInt(rawSize);
            packetStream.writeBytes(dataStream.data(), rawSize);
            break;
        };
        case CompressionType::Zlib:
        {
            if (rawSize >= this->m_CompressionThreshold)
            {
                uLong destSize = compressBound(rawSize);
                std::vector<uint8_t> compressedData(destSize);

                const int result = compress2(
                    compressedData.data(), &destSize,
                    dataStream.data(), rawSize,
                    Z_BEST_SPEED
                );

                if (result != Z_OK) {
                    packetStream.writeUnsignedVarInt(rawSize);
                    packetStream.writeBytes(dataStream.data(), rawSize);
                    break;
                };

                // Write compressed size, then data
                packetStream.writeUnsignedVarInt(destSize);
                packetStream.writeBytes(compressedData.data(), destSize);
            }
            else
            {
                // Below threshold, send raw
                packetStream.writeUnsignedVarInt(rawSize);
                packetStream.writeBytes(dataStream.data(), rawSize);
            };
            break;
        };
        case CompressionType::Snappy:
        {

            break;
        };
    };

    /*Logger::log(Logger::LogLevel::Debug,
        "Target: {} - {}: {}", static_cast<uint8_t>(subClientId), packet.getName(), packetStream.toString());*/
    this->m_NetworkServer->sendPacket(this->m_NetworkIdentifier, packetStream, reliability);
};