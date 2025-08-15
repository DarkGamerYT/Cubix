#ifndef UUID_HPP
#define UUID_HPP

#include <random>
#include <iomanip>
#include <regex>
#include <sstream>

namespace Util
{
    class UUID
    {
    private:
        uint64_t mMostSignificantBits, mLeastSignificantBits;

    public:
        explicit UUID(const uint64_t mostSignificantBits = 0, const uint64_t leastSignificantBits = 0)
            : mMostSignificantBits(mostSignificantBits), mLeastSignificantBits(leastSignificantBits) {};

        uint64_t getMostSignificantBits() const { return this->mMostSignificantBits; };
        uint64_t getLeastSignificantBits() const { return this->mLeastSignificantBits; };

        std::string toString() const;
        static bool canParse(const std::string&);
        static UUID fromString(const std::string&);
        static UUID randomUUID();
    };
};

#endif // !UUID_HPP