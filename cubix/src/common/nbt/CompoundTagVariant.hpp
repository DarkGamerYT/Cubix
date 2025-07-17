#ifndef COMPOUNDTAGVARIANT_HPP
#define COMPOUNDTAGVARIANT_HPP

#include <cstdint>
#include <sstream>
#include <iomanip>
#include <variant>
#include <functional>
#include <utility>
#include <vector>
#include <map>

#include "Tag.hpp"
#include "ByteTag.hpp"
#include "ShortTag.hpp"
#include "IntTag.hpp"
#include "Int64Tag.hpp"
#include "FloatTag.hpp"
#include "DoubleTag.hpp"
#include "StringTag.hpp"

namespace Nbt
{
    class CompoundTagVariant
    {
    private:
        std::shared_ptr<Tag> m_pTagStorage;

    public:
        /*CompoundTagVariant(UniqueTagPtr const& tag)
            : CompoundTagVariant(tag ? tag->copy() : nullptr) {};*/

        template <std::derived_from<Nbt::Tag> T>
        CompoundTagVariant(T tag)
            : m_pTagStorage(std::make_shared<T>(tag)) {};
        CompoundTagVariant(const std::unique_ptr<Nbt::Tag>& tag)
            : m_pTagStorage(std::move(tag->copy())) {};

        template <std::integral T>
        CompoundTagVariant(T integer) {
            size_t size = sizeof(T);
            if (size == sizeof(uint8_t)) {
                this->m_pTagStorage = std::make_shared<Nbt::ByteTag>(integer);
            }
            else if (size == sizeof(short)) {
                this->m_pTagStorage = std::make_shared<Nbt::ShortTag>(integer);
            }
            else if (size == sizeof(int)) {
                this->m_pTagStorage = std::make_shared<Nbt::IntTag>(integer);
            }
            else {
                this->m_pTagStorage = std::make_shared<Nbt::Int64Tag>(integer);
            };
        };
        CompoundTagVariant(uint8_t b)
            : m_pTagStorage(std::make_shared<Nbt::ByteTag>(b)) {};

        CompoundTagVariant(float f)
            : m_pTagStorage(std::make_shared<Nbt::FloatTag>(f)) {};

        CompoundTagVariant(double d)
            : m_pTagStorage(std::make_shared<Nbt::DoubleTag>(d)) {};

        CompoundTagVariant(const std::string& s)
            : m_pTagStorage(std::make_shared<Nbt::StringTag>(s)) {};

        CompoundTagVariant(const std::string_view& s)
            : m_pTagStorage(std::make_shared<Nbt::StringTag>(s.data())) {};

        template <size_t N>
        CompoundTagVariant(char const (&str)[N])
            : CompoundTagVariant(std::string_view{ str, N - 1 }) {};

        const Nbt::TagType index() const { return m_pTagStorage->getId(); };
        const Nbt::TagType getId() const { return index(); };

        template <std::derived_from<Tag> T>
        bool hold() const {
            return std::holds_alternative<T>(m_pTagStorage);
        };
        bool hold(Nbt::TagType type) const { return this->getId() == type; };

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
        bool is_primitive() const {
            return is_null() || is_string() || is_number() || is_binary();
        };
        bool is_structured() const { return is_array() || is_object(); };

        //const CompoundTag::TagMap const& items() const { return this->get<CompoundTag>().items(); }
        //const CompoundTag::TagMap& items() { return this->get<CompoundTag>().items(); }

        bool contains(const std::string& key) const;
        bool contains(const std::string& key, Nbt::TagType type) const;

        /*template <std::derived_from<Tag> T>
        bool contains(std::string_view key) const {
            size_t idx = Types::index<T>;
            return this->contains(key, (Nbt::TagType)idx);
        };*/

        const size_t size() const;

        template <std::derived_from<Nbt::Tag> T>
        T& get() { return this->m_pTagStorage; };

        template <std::derived_from<Nbt::Tag> T>
        T const& get() const { return this->m_pTagStorage; };

        Nbt::Tag& get() { return reinterpret_cast<Nbt::Tag&>(*m_pTagStorage); };
        Nbt::Tag const& get() const { return reinterpret_cast<Nbt::Tag const&>(*m_pTagStorage); };
    };
};

#endif // !COMPOUNDTAGVARIANT_HPP
