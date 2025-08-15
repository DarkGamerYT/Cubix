#ifndef GAMEVERSION_HPP
#define GAMEVERSION_HPP

#include <format>
#include <string>

#include "../../src-deps/semver/semver.hpp"

class GameVersion
{
private:
    uint16_t mMajor, mMinor, mPatch, mRevision;
    bool mIsBeta;

public:
    explicit GameVersion(
        const uint16_t major = 1,
        const uint16_t minor = 0,
        const uint16_t patch = 0,
        const uint16_t revision = 0,
        const bool isBeta = false
    ) : mMajor(major), mMinor(minor), mPatch(patch), mRevision(revision),
        mIsBeta(isBeta) {};

    uint16_t major() const { return this->mMajor; };
    uint16_t minor() const { return this->mMinor; };
    uint16_t patch() const { return this->mPatch; };
    uint16_t revision() const { return this->mRevision; };
    bool isBeta() const { return this->mIsBeta; };

    uint32_t encode() const
    {
        return (
            this->major() << 24
            | this->minor() << 16
            | this->patch() << 8
            | this->revision()
        );
    };
    static GameVersion decode(const uint32_t version)
    {
        const uint16_t major = (version >> 24) & 0xFF;
        const uint16_t minor = (version >> 16) & 0xFF;
        const uint16_t patch = (version >> 8) & 0xFF;
        const uint16_t revision = (version) & 0xFF;
        return GameVersion{ major, minor, patch, revision };
    };

    std::string asString() const
    {
        if (true == this->isBeta())
            return std::format("{}.{}.{}.{}", this->major(), this->minor(), this->patch(), this->revision());

        return std::format("{}.{}.{}", this->major(), this->minor(), this->patch());
    };

    semver::version semver() const
    {
        std::string str(this->isBeta() ? "preview" : "stable");
        if (true == this->isBeta())
            str.append("." + std::to_string(this->revision()));

        return { this->major(), this->minor(), this->patch(), str };
    };
};

#endif // !GAMEVERSION_HPP