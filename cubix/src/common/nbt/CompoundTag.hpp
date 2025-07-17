#ifndef COMPOUNDTAG_HPP
#define COMPOUNDTAG_HPP

#include "CompoundTagVariant.hpp"
#include "../util/StringUtils.hpp"

typedef std::unordered_map<std::string, Nbt::CompoundTagVariant> TagMap;
namespace Nbt
{
    class CompoundTag : public Nbt::Tag, public TagMap
    {
    public:
        using TagMap::unordered_map;

        template <std::derived_from<Nbt::Tag> T>
        CompoundTag& add(const std::string& name, const T& tag)
        {
            this->emplace(name, tag);
            return *this;
        };
        CompoundTag& add(const std::string& name, const std::unique_ptr<Nbt::Tag>& tag)
        {
            this->emplace(name, tag);
            return *this;
        };

        Nbt::TagType getId() const override { return Nbt::TagType::Compound; };
        std::unique_ptr<Tag> copy() const override {
            return std::make_unique<CompoundTag>(*this);
        };
        std::string toString() const override {
            std::stringstream stream;
            for (const auto& [key, value] : *this)
            {
                switch (value.getId())
                {
                    case Nbt::TagType::End:
                        break;

                    default:
                        stream
                            << "\n  // " << key << "\n  "
                            << Util::replace(value.get().toString(), "\n", "\n  ") << "\n";
                        break;
                };
            };

            return std::format("TAG_Compound: {} entries \n{{{}}}", this->size(), stream.str());
        };
    };
};

#endif // !COMPOUNDTAG_HPP
