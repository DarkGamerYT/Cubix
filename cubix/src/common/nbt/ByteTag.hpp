#ifndef BYTETAG_HPP
#define BYTETAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class ByteTag : public Nbt::Tag
    {
    private:
        uint8_t m_Value;

    public:
        ByteTag(uint8_t value = 0)
            : m_Value(value) {};

        void setValue(uint8_t value) { this->m_Value = value; };
        uint8_t getValue() const { return this->m_Value; };

        Nbt::TagType getId() const override { return Nbt::TagType::Byte; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<ByteTag>(*this);
        };
        std::string toString() const override {
            std::stringstream stream;
            stream
                << std::hex << std::setw(2) << std::setfill('0')
                << (this->m_Value & 0xFF);

            return std::format("TAG_Byte: {}", stream.str());
        };
    };
};

#endif // !BYTETAG_HPP