#ifndef TAGPTR_HPP
#define TAGPTR_HPP

#include "Tag.hpp"

namespace Nbt
{
    class TagPtr
    {
    private:
        std::shared_ptr<Nbt::Tag> p_mTag;

    public:
        Nbt::Tag* operator->() const { return p_mTag ? p_mTag.get() : nullptr; };
        Nbt::Tag* get() const { return p_mTag.get(); };
        explicit operator bool() const { return static_cast<bool>(p_mTag); };
        explicit operator std::shared_ptr<Nbt::Tag>()&& { return std::move(p_mTag); };
        explicit operator std::shared_ptr<Nbt::Tag>() const& { return p_mTag ? p_mTag->copy() : nullptr; };

    public:
        template <std::derived_from<Nbt::Tag> T>
        explicit TagPtr(const T& tag)
            : p_mTag(std::make_shared<T>(tag)) {};

        explicit TagPtr(const std::unique_ptr<Nbt::Tag>& tag)
            : p_mTag(std::move(tag->copy())) {};

        std::unique_ptr<Nbt::Tag> copy() const { return p_mTag ? p_mTag->copy() : nullptr; };
        Nbt::TagType index() const { return p_mTag ? p_mTag->getId() : Nbt::TagType::End; };
        Nbt::TagType getId() const { return this->index(); };

        bool holds(const Nbt::TagType type) const { return p_mTag && (this->getId() == type); };

        bool isArray() const {
            return this->holds(Nbt::TagType::List);
        };
        bool isBinary() const {
            return this->holds(Nbt::TagType::ByteArray)
                || this->holds(Nbt::TagType::IntArray);
        };
        bool isBoolean() const { return this->holds(Nbt::TagType::Byte); };
        bool isNull() const { return this->holds(Nbt::TagType::End); };
        bool isFloat() const {
            return this->holds(Nbt::TagType::Float)
                || this->holds(Nbt::TagType::Double);
        };
        bool isInteger() const {
            return this->holds(Nbt::TagType::Byte)
                || this->holds(Nbt::TagType::Short)
                || this->holds(Nbt::TagType::Int)
                || this->holds(Nbt::TagType::Int64);
        };
        bool isObject() const { return this->holds(Nbt::TagType::Compound); };
        bool isString() const { return this->holds(Nbt::TagType::String); };
        bool isNumber() const { return this->isFloat() || this->isInteger(); };
        bool isPrimitive() const { return this->isNull() || this->isString() || this->isNumber() || this->isBinary(); };
        bool isStructured() const { return this->isArray() || this->isObject(); };
    };
};

#endif // !TAGPTR_HPP
