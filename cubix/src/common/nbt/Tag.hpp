#ifndef TAG_HPP
#define TAG_HPP

#include <cstdint>
#include <memory>
#include <sstream>
#include <functional>
#include <iomanip>
#include <print>

#include "../util/Logger.hpp"

namespace Nbt
{
    enum class TagType : uint8_t {
        End       = 0x0,
        Byte      = 0x1,
        Short     = 0x2,
        Int       = 0x3,
        Int64     = 0x4,
        Float     = 0x5,
        Double    = 0x6,
        ByteArray = 0x7,
        String    = 0x8,
        List      = 0x9,
        Compound  = 0xA,
        IntArray  = 0xB
    };

    class Tag
    {
    public:
        virtual ~Tag() = default;

        virtual Nbt::TagType getId() const = 0;
        virtual std::string toString() const = 0;
        virtual std::unique_ptr<Tag> copy() const = 0;
    };

    // End Tag
    class EndTag : public Nbt::Tag
    {
    public:
        EndTag() {};

        Nbt::TagType getId() const override { return Nbt::TagType::End; };
        std::unique_ptr<Nbt::Tag> copy() const override {
            return std::make_unique<EndTag>(*this);
        };
        std::string toString() const override { return "TAG_End"; };
    };
};

#endif // !TAG_HPP
