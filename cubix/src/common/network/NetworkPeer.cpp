#include "NetworkPeer.hpp"
#include "NetworkServer.hpp"

BinaryStream& NetworkPeer::receivePacket(BinaryStream& stream) const {
    CompressionType compressionType = this->mCompression;
    if (this->isCompressed())
    {
        const auto& byte = stream.readByte();
        compressionType = static_cast<CompressionType>(byte);
    };

    if (compressionType == CompressionType::None ||
        compressionType == CompressionType::Disabled)
        return stream;

    const uint32_t unreadBytes = stream.bytesLeft();
    const auto& compressedData = stream.readBytes(unreadBytes);

    BinaryStream binaryStream{};
    switch (compressionType)
    {
        case CompressionType::Zlib:
        {
            z_stream zStream = {};
            zStream.next_in = const_cast<Bytef*>(compressedData);
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
            const auto& data = reinterpret_cast<const char*>(compressedData);
            if (!snappy::IsValidCompressedBuffer(data, unreadBytes))
            {
                stream = binaryStream;
                break;
            };

            size_t uncompressedLength;
            if (!snappy::GetUncompressedLength(data, unreadBytes, &uncompressedLength)) {
                stream = binaryStream;
                break;
            };

            std::vector<uint8_t> decompressedData(uncompressedLength);
            decompressedData.resize(uncompressedLength);

            if (!snappy::RawUncompress(
                data, unreadBytes,
                reinterpret_cast<char*>(decompressedData.data())
            )) {
                stream = binaryStream;
                break;
            };

            binaryStream.writeBytes(decompressedData.data(), decompressedData.size());
            stream = binaryStream;
            break;
        };
        default:
            break;
    };

    return stream;
};

void NetworkPeer::sendStream(const BinaryStream& dataStream, const NetworkPeer::Reliability reliability) const {
    if (this->mNetworkServer == nullptr)
        return;

    BinaryStream packetStream;
    packetStream.writeByte(0xFE);

    const size_t rawSize = dataStream.size();
    CompressionType compressionType = this->mCompression;

    if (this->isCompressed())
    {
        if (rawSize < this->mCompressionThreshold)
            compressionType = CompressionType::None;

        packetStream.writeByte(static_cast<uint8_t>(compressionType));
    };

    switch (compressionType)
    {
        case CompressionType::Disabled:
        case CompressionType::None:
        {
            packetStream.writeBytes(dataStream.data(), rawSize);
            break;
        };
        case CompressionType::Zlib:
        {
            z_stream zStream{};
            if (deflateInit2(&zStream, Z_BEST_SPEED, Z_DEFLATED, -MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK)
                throw std::runtime_error("Failed to initialize Zlib compressor");

            zStream.next_in = const_cast<Bytef*>(dataStream.data());
            zStream.avail_in = rawSize;

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
            std::string data;
            snappy::Compress(
                reinterpret_cast<const char*>(dataStream.data()), rawSize,
                &data
            );

            const std::vector<uint8_t> compressedData(data.begin(), data.end());
            packetStream.writeBytes(compressedData.data(), compressedData.size());
            break;
        };
    };

    /*Logger::log(Logger::LogLevel::Debug,
        "Target: {} - {}: {}", static_cast<uint8_t>(subClientId), packet.getName(), packetStream.toString());*/
    this->mNetworkServer->sendPacket(this->mNetworkIdentifier, packetStream, reliability);
};