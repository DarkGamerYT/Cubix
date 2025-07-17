#ifndef GAMEVERSION_HPP
#define GAMEVERSION_HPP

#include <sstream>
#include <string>

#include "../../src-deps/semver/semver.hpp"

class GameVersion
{
private:
    unsigned int m_Major, m_Minor, m_Patch, m_Revision;
    bool m_IsBeta;

public:
    GameVersion(
        const unsigned int major = 1,
        const unsigned int minor = 0,
        const unsigned int patch = 0,
        const unsigned int revision = 0,
        const bool isBeta = false
    ) : m_Major(major), m_Minor(minor), m_Patch(patch), m_Revision(revision),
        m_IsBeta(isBeta) {};

    unsigned int major() const { return this->m_Major; };
    unsigned int minor() const { return this->m_Minor; };
    unsigned int patch() const { return this->m_Patch; };
    unsigned int revision() const { return this->m_Revision; };
    bool isBeta() const { return this->m_IsBeta; };

    unsigned int encode() const
    {
        return (
            this->m_Major << 24
            | this->m_Minor << 16
            | this->m_Patch << 8
            | this->m_Revision | 1
        );
    };

    static GameVersion decode(unsigned int version)
    {
        unsigned int major = (version >> 24) & 0xFF;
        unsigned int minor = (version >> 16) & 0xFF;
        unsigned int patch = (version >> 8) & 0xFF;
        unsigned int revision = (version - 1) & 0xFF;
        return { major, minor, patch, revision };
    };

    std::string asString() const
    {
        std::stringstream stream;

        stream << this->m_Major;
        stream << "." << this->m_Minor;
        stream << "." << this->m_Patch;

        if (true == this->m_IsBeta)
            stream << "." << this->m_Revision;

        return stream.str();
    };

    semver::version semver() const
    {
        std::string str(this->m_IsBeta ? "preview" : "stable");
        if (true == this->m_IsBeta)
            str.append("." + std::to_string(this->m_Revision));

        return { this->m_Major, this->m_Minor, this->m_Patch, str };
    };
};

#endif // !GAMEVERSION_HPP