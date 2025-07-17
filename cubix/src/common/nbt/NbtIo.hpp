#ifndef NBTIO_HPP
#define NBTIO_HPP
#include <memory>

#include "Tag.hpp"
#include "ByteArrayTag.hpp"
#include "ByteTag.hpp"
#include "CompoundTag.hpp"
#include "DoubleTag.hpp"
#include "FloatTag.hpp"
#include "IntArrayTag.hpp"
#include "IntTag.hpp"
#include "Int64Tag.hpp"
#include "ListTag.hpp"
#include "ShortTag.hpp"
#include "StringTag.hpp"

#include "../util/BinaryStream.hpp"
#include "../util/Endianness.hpp"

namespace Nbt
{
    // Reading part
    template<Endianness E = Endianness::LittleEndian>
    short readShort(BinaryStream& stream)
    {
        switch (E)
        {
            case Endianness::BigEndian:
                return stream.readShort<Endianness::BigEndian>();
            case Endianness::LittleEndian:
            case Endianness::NetworkEndian:
                return stream.readShort<Endianness::LittleEndian>();
        };

        return (std::numeric_limits<short>::min)();
    };

    template<Endianness E = Endianness::LittleEndian>
    int32_t readInt(BinaryStream& stream)
    {
        switch (E)
        {
            case Endianness::BigEndian:
                return stream.readInt<Endianness::BigEndian>();
            case Endianness::LittleEndian:
                return stream.readInt<Endianness::LittleEndian>();
            case Endianness::NetworkEndian:
                return stream.readSignedVarInt();
        };

        return (std::numeric_limits<int32_t>::min)();
    };

    template<Endianness E = Endianness::LittleEndian>
    int64_t readLong(BinaryStream& stream)
    {
        switch (E)
        {
            case Endianness::BigEndian:
                return stream.readLong<Endianness::BigEndian>();
            case Endianness::LittleEndian:
                return stream.readLong<Endianness::LittleEndian>();
            case Endianness::NetworkEndian:
                return stream.readSignedVarLong();
        };

        return (std::numeric_limits<int64_t>::min)();
    };

    template<Endianness E = Endianness::LittleEndian>
    float readFloat(BinaryStream& stream)
    {
        switch (E)
        {
            case Endianness::BigEndian:
                return std::bit_cast<float>(stream.readInt<Endianness::BigEndian>());
            case Endianness::LittleEndian:
            case Endianness::NetworkEndian:
                return std::bit_cast<float>(stream.readInt<Endianness::LittleEndian>());
        };

        return (std::numeric_limits<float>::min)();
    };

    template<Endianness E = Endianness::LittleEndian>
    double readDouble(BinaryStream& stream)
    {
        switch (E)
        {
            case Endianness::BigEndian:
                return std::bit_cast<double>(stream.readLong<Endianness::BigEndian>());
            case Endianness::LittleEndian:
            case Endianness::NetworkEndian:
                return std::bit_cast<double>(stream.readLong<Endianness::LittleEndian>());
        };

        return (std::numeric_limits<double>::min)();
    };

    template<Endianness E = Endianness::LittleEndian>
    std::string readString(BinaryStream& stream)
    {
        size_t size = 0;
        switch (E)
        {
            case Endianness::BigEndian:
                size = stream.readShort<Endianness::BigEndian>(); break;
            case Endianness::LittleEndian:
                size = stream.readShort<Endianness::LittleEndian>(); break;
            case Endianness::NetworkEndian:
                size = stream.readUnsignedVarInt(); break;
        };

        std::vector<char> buffer(size);
        stream.readBytes(buffer.data(), size);

        return { buffer.begin(), buffer.end() };
    };

    template<Endianness E = Endianness::LittleEndian>
    std::unique_ptr<Nbt::Tag> read(
        BinaryStream& stream,
        bool shouldReadId = true,
        Nbt::TagType id = Nbt::TagType::Compound)
    {
        if (true == shouldReadId)
        {
            id = static_cast<Nbt::TagType>(stream.readByte());
        };

        if (static_cast<uint8_t>(id) > 11)
            return std::make_unique<Nbt::EndTag>();

        switch (id)
        {
            case Nbt::TagType::End:
                return std::make_unique<Nbt::EndTag>();
            case Nbt::TagType::Byte:
            {
                uint8_t value = stream.readByte();
                return std::make_unique<Nbt::ByteTag>(value);
            };
            case Nbt::TagType::Short:
            {
                short value = Nbt::readShort<E>(stream);
                return std::make_unique<Nbt::ShortTag>(value);
            };
            case Nbt::TagType::Int:
            {
                int32_t value = Nbt::readInt<E>(stream);
                return std::make_unique<Nbt::IntTag>(value);
            };
            case Nbt::TagType::Int64:
            {
                int64_t value = Nbt::readLong<E>(stream);
                return std::make_unique<Nbt::Int64Tag>(value);
            };
            case Nbt::TagType::Float:
            {
                float value = Nbt::readFloat<E>(stream);
                return std::make_unique<Nbt::FloatTag>(value);
            };
            case Nbt::TagType::Double:
            {
                double value = Nbt::readDouble<E>(stream);
                return std::make_unique<Nbt::DoubleTag>(value);
            };
            case Nbt::TagType::String:
            {
                const std::string& value = Nbt::readString<E>(stream);
                return std::make_unique<Nbt::StringTag>(value);
            };

            case Nbt::TagType::ByteArray:
            {
                Nbt::ByteArrayTag root;

                const int32_t size = Nbt::readInt<E>(stream);
                for (int i = 0; i < size; i++)
                {
                    uint8_t value = stream.readByte();
                    root.emplace_back(value);
                };

                return std::make_unique<Nbt::ByteArrayTag>(root);
            };
            case Nbt::TagType::IntArray:
            {
                Nbt::IntArrayTag root;

                const int32_t size = Nbt::readInt<E>(stream);
                for (int i = 0; i < size; i++)
                {
                    int32_t value = Nbt::readInt<E>(stream);
                    root.emplace_back(value);
                };

                return std::make_unique<Nbt::IntArrayTag>(root);
            };
            case Nbt::TagType::List:
            {
                Nbt::ListTag root;

                const auto listId = static_cast<Nbt::TagType>(stream.readByte());
                const int32_t size = Nbt::readInt<E>(stream);
                for (int i = 0; i < size; i++)
                {
                    const std::unique_ptr<Nbt::Tag>& value = Nbt::read<E>(stream, false, listId);
                    root.emplace_back(value);
                };

                return std::make_unique<Nbt::ListTag>(root);
            };
            case Nbt::TagType::Compound:
            {
                Nbt::CompoundTag root;
                if (true == shouldReadId)
                    Nbt::readString<E>(stream);

                do {
                    auto type = static_cast<Nbt::TagType>(stream.readByte());
                    if (type == Nbt::TagType::End)
                        break;

                    const std::string& name = Nbt::readString<E>(stream);
                    const std::unique_ptr<Nbt::Tag>& value = Nbt::read<E>(stream, false, type);
                    root.add(name, value);
                } while (stream.m_ReadPos < stream.size());

                return std::make_unique<Nbt::CompoundTag>(root);
            };
        };
    };

    // Writing part
    template<Endianness E = Endianness::LittleEndian>
    void writeShort(BinaryStream& stream, const short value)
    {
        switch (E)
        {
        case Endianness::BigEndian:
            stream.writeShort<Endianness::BigEndian>(value); break;
        case Endianness::LittleEndian:
        case Endianness::NetworkEndian:
            stream.writeShort<Endianness::LittleEndian>(value); break;
        };
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeInt(BinaryStream& stream, const int32_t value)
    {
        switch (E)
        {
        case Endianness::BigEndian:
            stream.writeInt<Endianness::BigEndian>(value); break;
        case Endianness::LittleEndian:
            stream.writeInt<Endianness::LittleEndian>(value); break;
        case Endianness::NetworkEndian:
            stream.writeSignedVarInt(value); break;
        };
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeLong(BinaryStream& stream, const int64_t value)
    {
        switch (E)
        {
        case Endianness::BigEndian:
            stream.writeLong<Endianness::BigEndian>(value); break;
        case Endianness::LittleEndian:
            stream.writeLong<Endianness::LittleEndian>(value); break;
        case Endianness::NetworkEndian:
            stream.writeSignedVarLong(value); break;
        };
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeFloat(BinaryStream& stream, const float value)
    {
        switch (E)
        {
            case Endianness::BigEndian:
            stream.writeInt<Endianness::BigEndian>(std::bit_cast<int32_t>(value)); break;
        case Endianness::LittleEndian:
        case Endianness::NetworkEndian:
            stream.writeInt<Endianness::LittleEndian>(std::bit_cast<int32_t>(value)); break;
        };
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeDouble(BinaryStream& stream, const double value)
    {
        switch (E)
        {
        case Endianness::BigEndian:
            stream.writeLong<Endianness::BigEndian>(std::bit_cast<int64_t>(value)); break;
        case Endianness::LittleEndian:
        case Endianness::NetworkEndian:
            stream.writeLong<Endianness::LittleEndian>(std::bit_cast<int64_t>(value)); break;
        };
    };

    template<Endianness E = Endianness::LittleEndian>
    void writeString(BinaryStream& stream, const std::string& value)
    {
        const size_t size = value.size();
        switch (E)
        {
        case Endianness::BigEndian:
            stream.writeShort<Endianness::BigEndian>(size); break;
        case Endianness::LittleEndian:
            stream.writeShort<Endianness::LittleEndian>(size); break;
        case Endianness::NetworkEndian:
            stream.writeUnsignedVarInt(size); break;
        };

        stream.writeBytes(value.data(), value.size());
    };

    template<Endianness E = Endianness::LittleEndian>
    void write(
        BinaryStream& stream,
        const std::unique_ptr<Nbt::Tag>& pTag,
        bool shouldWriteId = true,
        const std::string& name = "")
    {
        Nbt::TagType id = pTag->getId();
        if (true == shouldWriteId)
        {
            stream.writeByte(static_cast<uint8_t>(id));
            Nbt::writeString<E>(stream, name);
        };

        switch (id)
        {
            case Nbt::TagType::End: break;
            case Nbt::TagType::Byte:
            {
                const auto& root = reinterpret_cast<Nbt::ByteTag const&>(*pTag);
                stream.writeByte(root.getValue());
                break;
            };
            case Nbt::TagType::Short:
            {
                const auto& root = reinterpret_cast<Nbt::ShortTag const&>(*pTag);
                Nbt::writeShort<E>(stream, root.getValue());
                break;
            };
            case Nbt::TagType::Int:
            {
                const auto& root = reinterpret_cast<Nbt::IntTag const&>(*pTag);
                Nbt::writeInt<E>(stream, root.getValue());
                break;
            };
            case Nbt::TagType::Int64:
            {
                const auto& root = reinterpret_cast<Nbt::Int64Tag const&>(*pTag);
                Nbt::writeLong<E>(stream, root.getValue());
                break;
            };
            case Nbt::TagType::Float:
            {
                const auto& tag = reinterpret_cast<Nbt::FloatTag const&>(*pTag);
                Nbt::writeFloat<E>(stream, tag.getValue());
                break;
            };
            case Nbt::TagType::Double:
            {
                const auto& root = reinterpret_cast<Nbt::DoubleTag const&>(*pTag);
                Nbt::writeDouble<E>(stream, root.getValue());
                break;
            };
            case Nbt::TagType::String:
            {
                const auto& root = reinterpret_cast<Nbt::StringTag const&>(*pTag);
                Nbt::writeString<E>(stream, root.getValue());
                break;
            };

            case Nbt::TagType::ByteArray:
            {
                const auto& root = reinterpret_cast<Nbt::ByteArrayTag const&>(*pTag);

                Nbt::writeInt<E>(stream, static_cast<int32_t>(root.size()));
                for (const uint8_t value : root)
                    stream.writeByte(value);

                break;
            };
            case Nbt::TagType::IntArray:
            {
                const auto& root = reinterpret_cast<Nbt::IntArrayTag const&>(*pTag);

                Nbt::writeInt<E>(stream, static_cast<int32_t>(root.size()));
                for (int value : root)
                    Nbt::writeInt<E>(stream, value);

                break;
            };
            case Nbt::TagType::List:
            {
                const auto& root = reinterpret_cast<Nbt::ListTag const&>(*pTag);

                stream.writeByte(static_cast<uint8_t>(root.getId()));
                Nbt::writeInt<E>(stream, static_cast<int32_t>(root.size()));
                for (auto& value : root)
                {
                    const std::unique_ptr<Nbt::Tag>& pValue = value.copy();
                    Nbt::write<E>(stream, pValue, false);
                };

                break;
            };
            case Nbt::TagType::Compound:
            {
                const auto& root = reinterpret_cast<Nbt::CompoundTag const&>(*pTag);
                for (auto& [key, value] : root)
                {
                    const std::unique_ptr<Nbt::Tag>& pValue = value.get().copy();
                    Nbt::write<E>(stream, pValue, true, key);
                };

                stream.writeByte(static_cast<uint8_t>(Nbt::TagType::End));
                break;
            };
        };
    };
};

#endif // !NBTIO_HPP
