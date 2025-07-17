#ifndef TAGPTR_HPP
#define TAGPTR_HPP

#include "Tag.hpp"

namespace Nbt
{
    class TagPtr
    {
    private:
        std::shared_ptr<Nbt::Tag> m_pTag;

    public:
        Nbt::Tag* operator->() const { return m_pTag ? m_pTag.get() : nullptr; };
        Nbt::Tag* get() const { return m_pTag.get(); };
        explicit operator bool() const { return static_cast<bool>(m_pTag); };
        operator std::shared_ptr<Nbt::Tag>()&& { return std::move(m_pTag); };
        operator std::shared_ptr<Nbt::Tag>() const& { return m_pTag ? m_pTag->copy() : nullptr; };

    public:
        template <std::derived_from<Nbt::Tag> T>
        TagPtr(const T& tag)
            : m_pTag(std::make_shared<T>(tag)) {};
        TagPtr(const std::unique_ptr<Nbt::Tag>& tag)
            : m_pTag(std::move(tag->copy())) {};

        std::unique_ptr<Nbt::Tag> copy() const { return m_pTag ? m_pTag->copy() : nullptr; };
        Nbt::TagType index() const { return m_pTag ? m_pTag->getId() : Nbt::TagType::End; };
        Nbt::TagType getId() const { return this->index(); };

        bool hold(Nbt::TagType type) const { return m_pTag && (this->getId() == type); };

        bool is_array() const { return hold(Nbt::TagType::List); };
        bool is_binary() const { return hold(Nbt::TagType::ByteArray) || hold(Nbt::TagType::IntArray); };
        bool is_boolean() const { return hold(Nbt::TagType::Byte); };
        bool is_null() const { return hold(Nbt::TagType::End); };
        bool is_number_float() const { return hold(Nbt::TagType::Float) || hold(Nbt::TagType::Double); };
        bool is_number_integer() const {
            return hold(Nbt::TagType::Byte) || hold(Nbt::TagType::Short) || hold(Nbt::TagType::Int) || hold(Nbt::TagType::Int64);
        };
        bool is_object() const { return hold(Nbt::TagType::Compound); };
        bool is_string() const { return hold(Nbt::TagType::String); };
        bool is_number() const { return is_number_float() || is_number_integer(); };
        bool is_primitive() const { return is_null() || is_string() || is_number() || is_binary(); };
        bool is_structured() const { return is_array() || is_object(); };
    };
};

#endif // !TAGPTR_HPP
