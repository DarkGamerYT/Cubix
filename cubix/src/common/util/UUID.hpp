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
        uint64_t m_MostSignificantBits, m_LeastSignificantBits;

    public:
        UUID(uint64_t mostSignificantBits = 0, uint64_t leastSignificantBits = 0)
            : m_MostSignificantBits(mostSignificantBits), m_LeastSignificantBits(leastSignificantBits) {};

        uint64_t getMostSignificantBits() const { return this->m_MostSignificantBits; };
        uint64_t getLeastSignificantBits() const { return this->m_MostSignificantBits; };

        std::string toString() const;
        static bool canParse(const std::string&);
        static UUID fromString(const std::string&);
        static UUID randomUUID();
    };
};

#endif // !UUID_HPP