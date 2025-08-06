#ifndef BYTETAG_HPP
#define BYTETAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class ByteTag final : public Nbt::Tag
    {
    private:
        uint8_t mValue;

    public:
        explicit ByteTag(const uint8_t value = 0)
            : mValue(value) {};

        void setValue(const uint8_t value) { this->mValue = value; };
        uint8_t getValue() const { return this->mValue; };

        Nbt::TagType getId() const override { return Nbt::TagType::Byte; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<ByteTag>(*this);
        };

        std::string toString() const override {
            std::stringstream stream;
            stream
                << std::hex << std::setw(2) << std::setfill('0')
                << (this->mValue & 0xFF);

            return std::format("TAG_Byte: {}", stream.str());
        };
    };
};

#endif // !BYTETAG_HPP