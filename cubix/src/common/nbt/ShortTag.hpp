#ifndef SHORTTAG_HPP
#define SHORTTAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class ShortTag final : public Nbt::Tag
    {
    private:
        short mValue;

    public:
        explicit ShortTag(const short value = 0)
            : mValue(value) {};

        void setValue(const short value) { this->mValue = value; };
        short getValue() const { return this->mValue; };

        Nbt::TagType getId() const override { return Nbt::TagType::Short; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<ShortTag>(*this);
        };
        
        std::string toString() const override {
            return std::format("TAG_Short: {}", this->mValue);
        };
    };
};

#endif // !SHORTTAG_HPP