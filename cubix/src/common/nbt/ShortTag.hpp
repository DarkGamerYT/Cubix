#ifndef SHORTTAG_HPP
#define SHORTTAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class ShortTag : public Nbt::Tag
    {
    private:
        short m_Value;

    public:
        ShortTag(short value = 0)
            : m_Value(value) {};

        void setValue(short value) { this->m_Value = value; };
        short getValue() const { return this->m_Value; };

        Nbt::TagType getId() const override { return Nbt::TagType::Short; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<ShortTag>(*this);
        };
        std::string toString() const override {
            return std::format("TAG_Short: {}", this->m_Value);
        };
    };
};

#endif // !SHORTTAG_HPP