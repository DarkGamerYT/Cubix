#ifndef STRINGTAG_HPP
#define STRINGTAG_HPP

#include "Tag.hpp"

namespace Nbt
{
    class StringTag final : public Nbt::Tag
    {
    private:
        std::string m_Value;

    public:
        StringTag() = default;
        explicit StringTag(const std::string& value)
            : m_Value(value) {};

        void setValue(const std::string& value) { this->m_Value = value; };
        std::string getValue() const { return this->m_Value; };

        Nbt::TagType getId() const override { return Nbt::TagType::String; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<StringTag>(*this);
        };

        std::string toString() const override {
            return std::format("TAG_String: {}", this->m_Value);
        };
    };
};

#endif // !STRINGTAG_HPP