#ifndef LISTTAG_HPP
#define LISTTAG_HPP

#include <vector>
#include "Tag.hpp"
#include "TagPtr.hpp"

typedef std::vector<Nbt::TagPtr> ListType;
namespace Nbt
{
    class ListTag : public Nbt::Tag, public ListType
    {
    private:
        Nbt::TagType m_Type;

    public:
        ListTag(ListType tags = {}, Nbt::TagType type = Nbt::TagType::End)
            : ListType(std::move(tags)), m_Type(type)
        {
            if (!this->empty())
                this->m_Type = front()->getId();
        };

        Nbt::TagType getId() const override { return Nbt::TagType::List; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<ListTag>(*this);
        };
        std::string toString() const override {
            std::stringstream stream;
            for (size_t i = 0; i < this->size(); i++)
            {
                const auto& value = this->at(i);
                switch (value.getId())
                {
                    case Nbt::TagType::End:
                        break;

                    default:
                        stream
                            << "  "
                            << value.get()->toString() << "\n";
                        break;
                };
            };

            return std::format("ListTag  ({} entries) {{\n{}}}", this->size(), stream.str());
        };
    };
};

#endif // !LISTTAG_HPP
