#ifndef FLOATTAG_HPP
#define FLOATTAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class FloatTag final : public Nbt::Tag
    {
    private:
        float mValue;

    public:
        explicit FloatTag(const float value = 0)
            : mValue(value) {};

        void setValue(const float value) { this->mValue = value; };
        float getValue() const { return this->mValue; };

        Nbt::TagType getId() const override { return Nbt::TagType::Float; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<FloatTag>(*this);
        };

        std::string toString() const override {
            return std::format("TAG_Float: {}", this->mValue);
        };
    };
};

#endif // !FLOATTAG_HPP