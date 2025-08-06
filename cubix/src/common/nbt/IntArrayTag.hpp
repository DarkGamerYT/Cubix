#ifndef INTARRAYTAG_HPP
#define INTARRAYTAG_HPP

#include <vector>
#include "Tag.hpp"

namespace Nbt
{
    class IntArrayTag final : public Nbt::Tag, public std::vector<int32_t>
    {
    public:
        using std::vector<int32_t>::vector;

        Nbt::TagType getId() const override { return Nbt::TagType::ByteArray; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<IntArrayTag>(*this);
        };

        std::string toString() const override {
            return std::format("TAG_IntArray: [{} bytes]", this->size());
        };
    };
};

#endif // !INTARRAYTAG_HPP