#ifndef BYTEARRAYTAG_HPP
#define BYTEARRAYTAG_HPP

#include <vector>
#include "Tag.hpp"

namespace Nbt
{
    class ByteArrayTag final : public Nbt::Tag, public std::vector<uint8_t>
    {
    public:
        using std::vector<uint8_t>::vector;

        Nbt::TagType getId() const override { return Nbt::TagType::ByteArray; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<ByteArrayTag>(*this);
        };

        std::string toString() const override {
            size_t size = this->size();

            std::stringstream stream;
            stream << std::hex << std::setfill('0');

            for (size_t i = 0; i < size; i++)
            {
                const uint8_t value = this->at(i);
                stream << std::setw(2) << (value & 0xFF);

                if (i < size - 1)
                    stream << " ";
            };

            return std::format("TAG_ByteArray: {} [{} bytes]", stream.str(), size);
        };
    };
};

#endif // !BYTEARRAYTAG_HPP