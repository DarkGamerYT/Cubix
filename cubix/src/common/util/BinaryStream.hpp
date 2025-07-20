#ifndef BINARYSTREAM_HPP
#define BINARYSTREAM_HPP

#include <string>
#include <span>
#include <bit>
#include <cstring>
#include <stdexcept>

#include "Logger.hpp"
#include "Endianness.hpp"

#include "../world/level/BlockPos.hpp"
#include "../world/level/ChunkPos.hpp"
#include "../world/item/Item.hpp"

#include "UUID.hpp"

class BinaryStream
{
public:
    std::vector<uint8_t> m_Stream;
    size_t m_ReadPos = 0;

public:
    BinaryStream() = default;
    explicit BinaryStream(const std::vector<uint8_t>& data)
        : m_Stream(data) {};

    const uint8_t* data() const { return this->m_Stream.data(); };
    size_t size() const { return this->m_Stream.size(); };
    size_t bytesLeft() const {
        return this->m_Stream.size() - this->m_ReadPos;
    };
    void reset() { this->m_ReadPos = 0; };


    // Readers
    uint8_t* readBytes(const size_t length) {
        if (length > this->bytesLeft())
            throw std::out_of_range(
                std::format(
                    "Read past end. Pos: {}, size: {}",
                    this->m_ReadPos + length, this->m_Stream.size()
                )
            );

        uint8_t* ptr = this->m_Stream.data() + this->m_ReadPos;
        this->m_ReadPos += length;
        return ptr;
    };

    uint8_t readByte() {
        return this->read<uint8_t>();
    };

    int8_t readSignedByte() {
        const auto value = this->readByte();
        return static_cast<int8_t>(value);
    };


    template<typename T>
    T read() {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Unsupported type for BinaryStream::read");

        const uint8_t* ptr = this->readBytes(sizeof(T));

        // Read the value from the byte buffer
        T value;
        std::memcpy(&value, ptr, sizeof(T));

        return value;
    };

    uint32_t readUnsignedVarInt() {
        uint32_t value = 0;
        int shift = 0;
        for (int i = 0; i < 5; i ++)
        {
            const uint8_t toRead = this->readByte();

            if (i == 4 && (toRead & 0x80))
                throw std::runtime_error("Malformed VarInt: too many bytes");

            value |= ((toRead & 0x7f) <<  shift);
            if ((toRead & 0x80) == 0)
                return value;

            shift += 7;
        };

        throw std::runtime_error("VarInt is too big or malformed");
    };

    int32_t readSignedVarInt() {
        const uint32_t raw = this->readUnsignedVarInt();
        return static_cast<int32_t>(raw >> 1) ^ -static_cast<int32_t>(raw & 1);
    };

    template<Endianness E = Endianness::LittleEndian>
    uint32_t readUnsignedInt() {
        auto value = this->read<uint32_t>();
        if constexpr (E == Endianness::BigEndian)
            value = std::byteswap(value);

        return value;
    };

    template<Endianness E = Endianness::LittleEndian>
    int32_t readInt() {
        const uint32_t raw = this->readUnsignedInt<E>();
        return static_cast<int32_t>(raw);
    };

    template<Endianness E = Endianness::LittleEndian>
    unsigned short readUnsignedShort() {
        auto value = this->read<unsigned short>();
        if constexpr (E == Endianness::BigEndian)
            value = std::byteswap(value);

        return value;
    };

    template<Endianness E = Endianness::LittleEndian>
    short readShort() {
        const unsigned short raw = this->readUnsignedShort<E>();
        return static_cast<short>(raw);
    };

    uint64_t readUnsignedVarLong() {
        uint64_t value = 0;
        for (int i = 0; i < 10; i ++)
        {
            const uint8_t toRead = this->readByte();

            if (i == 9 && (toRead & 0x80))
                throw std::runtime_error("Malformed VarLong: too many bytes");

            value |= (static_cast<uint64_t>(toRead & 0x7f) << static_cast<uint64_t>(7 * i));
            if ((toRead & 0x80) == 0)
                return value;
        };

        throw std::runtime_error("VarLong is too big or malformed");
    };

    int64_t readSignedVarLong() {
        const uint64_t raw = this->readUnsignedVarLong();
        return static_cast<int64_t>(raw >> 1) ^ -static_cast<int64_t>(raw & 1);
    };

    template<Endianness E = Endianness::LittleEndian>
    uint64_t readUnsignedLong() {
        auto value = this->read<uint64_t>();
        if constexpr (E == Endianness::BigEndian)
            value = std::byteswap(value);

        return value;
    };

    template<Endianness E = Endianness::LittleEndian>
    int64_t readLong() {
        const uint64_t raw = this->readUnsignedLong<E>();
        return static_cast<int64_t>(raw);
    };

    template<Endianness E = Endianness::LittleEndian>
    std::string readString() {
        unsigned int length;
        if constexpr (E == Endianness::NetworkEndian)
            length = this->readUnsignedVarInt();
        else
            length = this->readUnsignedInt<E>();

        if (this->m_ReadPos + length > m_Stream.size())
            throw std::out_of_range("Read past end while reading string");

        using difference = std::vector<unsigned char>::difference_type;
        const auto start = m_Stream.begin() + static_cast<difference>(m_ReadPos);
        const auto end = std::next(start, length);

        this->m_ReadPos += length;
        return { start, end };
    };

    Util::UUID readUUID() {
        uint64_t mostSignificantBits = this->readUnsignedLong();
        uint64_t leastSignificantBits = this->readUnsignedLong();

        return { mostSignificantBits, leastSignificantBits };
    };

    bool readBoolean() { return this->readByte() != 0; };

    Vec3 readVec3() {
        auto x = static_cast<double>(this->read<float>());
        auto y = static_cast<double>(this->read<float>());
        auto z = static_cast<double>(this->read<float>());

        return { x, y, z };
    };

    BlockPos readNetworkBlockPosition() {
        auto x = static_cast<double>(this->readSignedVarInt());
        auto y = static_cast<double>(this->readUnsignedVarInt());
        auto z = static_cast<double>(this->readSignedVarInt());

        return { x, y, z };
    };
    BlockPos readBlockPosition() {
        auto x = static_cast<double>(this->readSignedVarInt());
        auto y = static_cast<double>(this->readSignedVarInt());
        auto z = static_cast<double>(this->readSignedVarInt());

        return { x, y, z };
    };
    ChunkPos readChunkPos() {
        int x = this->readSignedVarInt();
        int z = this->readSignedVarInt();

        return { x, z };
    };

    // Writers
    void writeBytes(const void* data, const size_t length) {
        const auto* bytes = static_cast<const uint8_t*>(data);
        this->m_Stream.insert(this->m_Stream.end(), bytes, bytes + length);
    };

    template<typename T>
    void write(T value) {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Unsupported type for BinaryStream::write");
        this->writeBytes(&value, sizeof(T));
    };

    void writeByte(const uint8_t value) {
        this->write<uint8_t>(value);
    };

    void writeSignedByte(const int8_t value) {
        this->writeByte(static_cast<uint8_t>(value));
    };

    void writeUnsignedVarInt(uint32_t value) {
        value &= 0xffffffff;
        for (int i = 0; i < 5; ++i)
        {
            const uint8_t toWrite = value & 0x7f;
            value >>= 7;

            if (value != 0)
            {
                this->writeByte(toWrite | 0x80);
                continue;
            };

            this->writeByte(toWrite);
            break;
        };
    };
    void writeSignedVarInt(const int32_t value)
    {
        this->writeUnsignedVarInt(
            ((static_cast<uint32_t>(value) << 1) ^ static_cast<uint32_t>(value >> 31)) & 0xFFFFFFFFL
        );
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeUnsignedInt(uint32_t value)
    {
        if constexpr (E == Endianness::BigEndian)
            value = std::byteswap(value);

        this->write<uint32_t>(value);
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeInt(const int32_t value) {
        this->writeUnsignedInt<E>(value);
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeUnsignedShort(unsigned short value) {
        if constexpr (E == Endianness::BigEndian)
            value = std::byteswap(value);

        this->write<unsigned short>(value);
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeShort(const short value) {
        this->writeUnsignedShort<E>(value);
    };

    void writeUnsignedVarLong(uint64_t value) {
        value &= 0xffffffffffffffff;
        for (int i = 0; i < 10; ++i)
        {
            const uint8_t toWrite = value & 0x7f;
            value >>= 7;

            if (value != 0)
            {
                this->writeByte(toWrite | 0x80);
                continue;
            };

            this->writeByte(toWrite);
            break;
        };
    };
    void writeSignedVarLong(const int64_t value) {
        this->writeUnsignedVarLong(
            (static_cast<uint64_t>(value) << 1) ^ static_cast<uint64_t>(value >> 63)
        );
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeUnsignedLong(uint64_t value) {
        if constexpr (E == Endianness::BigEndian)
            value = std::byteswap(value);

        this->write<uint64_t>(value);
    };
    
    template<Endianness E = Endianness::LittleEndian>
    void writeLong(const int64_t value) {
        this->writeUnsignedLong<E>(value);
    };


    void writeBoolean(const bool value) {
        this->writeByte(value ? 1 : 0);
    };

    void writeVec3(const Vec3& vec) {
        this->write<float>(static_cast<float>(vec.x));
        this->write<float>(static_cast<float>(vec.y));
        this->write<float>(static_cast<float>(vec.z));
    };

    void writeVec2(const double x, const double y) {
        this->write<float>(static_cast<float>(x));
        this->write<float>(static_cast<float>(y));
    };

    void writeNetworkBlockPosition(const int x, const unsigned int y, const int z) {
        this->writeSignedVarInt(x);
        this->writeUnsignedVarInt(y);
        this->writeSignedVarInt(z);
    };
    void writeNetworkBlockPosition(const BlockPos& pos) {
        this->writeSignedVarInt(static_cast<int32_t>(pos.x));
        this->writeUnsignedVarInt(static_cast<uint32_t>(pos.y));
        this->writeSignedVarInt(static_cast<int32_t>(pos.z));
    };

    void writeBlockPosition(const int x, const int y, const int z) {
        this->writeSignedVarInt(x);
        this->writeSignedVarInt(y);
        this->writeSignedVarInt(z);
    };
    void writeBlockPosition(const BlockPos& pos) {
        this->writeSignedVarInt(static_cast<int32_t>(pos.x));
        this->writeSignedVarInt(static_cast<int32_t>(pos.y));
        this->writeSignedVarInt(static_cast<int32_t>(pos.z));
    };

    void writeChunkPos(const int x, int const z) {
        this->writeSignedVarInt(x);
        this->writeSignedVarInt(z);
    };
    void writeChunkPos(const ChunkPos& pos) {
        this->writeSignedVarInt(pos.x);
        this->writeSignedVarInt(pos.z);
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeString(const std::string& value) {
        if constexpr (E == Endianness::NetworkEndian)
            this->writeUnsignedVarInt(static_cast<uint32_t>(value.size()));
        else
            this->writeUnsignedInt<E>(static_cast<uint32_t>(value.size()));
        this->writeBytes(value.data(), value.size());
    };

    void writeUUID(const Util::UUID& value) {
        this->writeUnsignedLong(value.getMostSignificantBits());
        this->writeUnsignedLong(value.getLeastSignificantBits());
    };

    void writeItem(const Item& item, bool includeNetId = false);

    std::string toString() const
    {
        const size_t streamSize = this->m_Stream.size();
        std::stringstream messageData;
        for (size_t i = 0; i < streamSize; i++)
        {
            messageData
                << "0x" << std::setw(2) << std::setfill('0')
                << std::hex << (0xFF & static_cast<unsigned int>(this->m_Stream[i]));

            if (i != streamSize - 1)
                messageData << ", ";
        };

        return messageData.str();
    };
};

#endif // !BINARYSTREAM_HPP