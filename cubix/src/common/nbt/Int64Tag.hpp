#ifndef INT64TAG_HPP
#define INT64TAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class Int64Tag : public Nbt::Tag
    {
    private:
        int64_t m_Value;

    public:
        Int64Tag(int64_t value = 0)
            : m_Value(value) {};

        void setValue(int64_t value) { this->m_Value = value; };
        int64_t getValue() const { return this->m_Value; };

        Nbt::TagType getId() const override { return Nbt::TagType::Int64; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<Int64Tag>(*this);
        };
        std::string toString() const override {
            return std::format("TAG_Long: {}", this->m_Value);
        };
    };
};

#endif // !INT64TAG_HPP