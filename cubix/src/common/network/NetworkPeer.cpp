#include "NetworkPeer.hpp"
#include "NetworkServer.hpp"
#include "RakMemoryOverride.h"

BinaryStream& NetworkPeer::receivePacket(BinaryStream& stream) const {
    CompressionType compressionType = this->m_Compression;
    if (this->isCompressed())
    {
        const auto& byte = stream.readByte();
        compressionType = static_cast<CompressionType>(byte);
    };

    switch (compressionType)
    {
        case CompressionType::Zlib:
        {
            BinaryStream binaryStream{};

            const uint32_t unreadBytes = stream.bytesLeft();
            Bytef* compressedData = stream.m_Stream.data() + stream.m_ReadPos;

            z_stream zStream = {};
            zStream.next_in = compressedData;
            zStream.avail_in = unreadBytes;

            if (inflateInit2(&zStream, -MAX_WBITS) != Z_OK) {
                stream = binaryStream;
                break;
            };

            std::vector<uint8_t> decompressedData;
            int inflateResult = Z_OK;

            do {
                constexpr size_t chunkSize = 4096;
                const size_t startSize = decompressedData.size();
                decompressedData.resize(startSize + chunkSize);

                zStream.next_out = decompressedData.data() + startSize;
                zStream.avail_out = chunkSize;

                inflateResult = inflate(&zStream, Z_NO_FLUSH);
            } while (inflateResult == Z_OK);

            inflateEnd(&zStream);

            if (inflateResult != Z_STREAM_END) {
                stream = binaryStream;
                break;
            };

            decompressedData.resize(zStream.total_out); // Trim excess

            binaryStream.writeBytes(decompressedData.data(), decompressedData.size());
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

void NetworkPeer::sendPacket(Packet& packet, SubClientId subClientId, NetworkPeer::Reliability reliability) const {
    BinaryStream packetStream;
    packetStream.writeByte(0xFE);

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

    // Write packet data
    packet.write(dataStream);

    const size_t rawSize = dataStream.size();
    CompressionType compressionType = this->m_Compression;

    if (this->isCompressed())
    {
        if (rawSize < this->m_CompressionThreshold)
            compressionType = CompressionType::None;

        packetStream.writeByte(static_cast<uint8_t>(compressionType));
    };

    BinaryStream binaryStream{};
    binaryStream.writeUnsignedVarInt(rawSize);
    binaryStream.writeBytes(dataStream.data(), rawSize);

    switch (compressionType)
    {
        case CompressionType::Disabled:
        case CompressionType::None:
        {
            packetStream.writeBytes(binaryStream.data(), binaryStream.size());
            break;
        };
        case CompressionType::Zlib:
        {
            z_stream zStream{};
            if (deflateInit2(&zStream, Z_BEST_SPEED, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK)
                throw std::runtime_error("Failed to initialize Zlib compressor");

            zStream.next_in = const_cast<Bytef*>(binaryStream.data());
            zStream.avail_in = binaryStream.size();

            std::vector<uint8_t> compressedData;
            int deflateResult;

            do {
                constexpr size_t chunkSize = 4096;
                const size_t currentSize = compressedData.size();
                compressedData.resize(currentSize + chunkSize);

                zStream.next_out = compressedData.data() + currentSize;
                zStream.avail_out = chunkSize;

                deflateResult = deflate(&zStream, Z_FINISH);
                if (deflateResult == Z_STREAM_ERROR) {
                    deflateEnd(&zStream);
                    throw std::runtime_error("Zlib compression stream error");
                };
            } while (deflateResult != Z_STREAM_END);

            deflateEnd(&zStream);
            compressedData.resize(zStream.total_out); // Trim to actual size

            packetStream.writeBytes(compressedData.data(), compressedData.size());
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