#ifndef INTTAG_HPP
#define INTTAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class IntTag : public Nbt::Tag
    {
    private:
        int m_Value;

    public:
        IntTag(int value = 0)
            : m_Value(value) {};

        void setValue(int value) { this->m_Value = value; };
        int getValue() const { return this->m_Value; };

        Nbt::TagType getId() const override { return Nbt::TagType::Int; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<IntTag>(*this);
        };
        std::string toString() const override {
            return std::format("TAG_Int: {}", this->m_Value);
        };
    };
};

#endif // !INTTAG_HPP