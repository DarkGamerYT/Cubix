#ifndef FLOATTAG_HPP
#define FLOATTAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class FloatTag : public Nbt::Tag
    {
    private:
        float m_Value;

    public:
        FloatTag(float value = 0)
            : m_Value(value) {};

        void setValue(float value) { this->m_Value = value; };
        float getValue() const { return this->m_Value; };

        Nbt::TagType getId() const override { return Nbt::TagType::Float; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<FloatTag>(*this);
        };
        std::string toString() const override {
            return std::format("TAG_Float: {}", this->m_Value);
        };
    };
};

#endif // !FLOATTAG_HPP