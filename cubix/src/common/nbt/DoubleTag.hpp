#ifndef DOUBLETAG_HPP
#define DOUBLETAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class DoubleTag final : public Nbt::Tag
    {
    private:
        double mValue;

    public:
        explicit DoubleTag(const double value = 0)
            : mValue(value) {};

        void setValue(const double value) { this->mValue = value; };
        double getValue() const { return this->mValue; };

        Nbt::TagType getId() const override { return Nbt::TagType::Double; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<DoubleTag>(*this);
        };

        std::string toString() const override {
            return std::format("TAG_Double: {}", this->mValue);
        };
    };
};

#endif // !DOUBLETAG_HPP