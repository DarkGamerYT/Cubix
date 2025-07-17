#ifndef DOUBLETAG_HPP
#define DOUBLETAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class DoubleTag : public Nbt::Tag
    {
    private:
        double m_Value;

    public:
        DoubleTag(double value = 0)
            : m_Value(value) {};

        void setValue(double value) { this->m_Value = value; };
        double getValue() const { return this->m_Value; };

        Nbt::TagType getId() const override { return Nbt::TagType::Double; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<DoubleTag>(*this);
        };
        std::string toString() const override {
            return std::format("TAG_Double: {}", this->m_Value);
        };
    };
};

#endif // !DOUBLETAG_HPP