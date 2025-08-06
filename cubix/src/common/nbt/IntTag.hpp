#ifndef INTTAG_HPP
#define INTTAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class IntTag final : public Nbt::Tag
    {
    private:
        int mValue;

    public:
        explicit IntTag(const int value = 0)
            : mValue(value) {};

        void setValue(const int value) { this->mValue = value; };
        int getValue() const { return this->mValue; };

        Nbt::TagType getId() const override { return Nbt::TagType::Int; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<IntTag>(*this);
        };
        
        std::string toString() const override {
            return std::format("TAG_Int: {}", this->mValue);
        };
    };
};

#endif // !INTTAG_HPP