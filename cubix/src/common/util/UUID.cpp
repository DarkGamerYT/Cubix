#include "UUID.hpp"
namespace Util
{
    bool UUID::canParse(const std::string& value)
    {
        static std::regex regex("[a-fA-F0-9]{8}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{4}-[a-fA-F0-9]{12}");

        std::smatch regexMatch;
        return (
            std::regex_search(value, regexMatch, regex)
            && value.length() == regexMatch[0].length());
    };

    std::string UUID::toString() const
    {
        std::stringstream stream;
        stream << std::hex << std::setfill('0')
            << std::setw(8) << static_cast<uint32_t>(mMostSignificantBits >> 32) << "-"
            << std::setw(4) << static_cast<uint16_t>(mMostSignificantBits >> 16) << "-"
            << std::setw(4) << static_cast<uint16_t>(mMostSignificantBits) << "-"
            << std::setw(4) << static_cast<uint16_t>(mLeastSignificantBits >> 48) << "-"
            << std::setw(12) << (mLeastSignificantBits & 0x0000FFFFFFFFFFFFULL);

        return stream.str();
    };

    UUID UUID::fromString(const std::string& value) {
        uint64_t mostSignificantBits = 0, leastSignificantBits = 0;
        if (UUID::canParse(value))
        {
            int count = 0;
            for (const char& c : value)
            {
                if (c == '-')
                    continue;

                uint64_t ca = 0;
                if (c >= '0' && c <= '9')
                    ca = c - '0';

                else if (c >= 'a' && c <= 'f')
                    ca = c - 'a' + 10;

                else if (c >= 'A' && c <= 'F')
                    ca = c - 'A' + 10;

                else break;

                if (++count > 16)
                    leastSignificantBits |= ca << (0x80 - (4 * count));
                else {
                    mostSignificantBits |= ca << (0x40 - (4 * count));
                };
            };
        };

        return Util::UUID{ mostSignificantBits, leastSignificantBits };
    };

    UUID UUID::randomUUID()
    {
        static std::mt19937_64 gen(std::random_device{}());
        std::uniform_int_distribution<uint64_t> distrib;

        uint64_t mostSignificantBits = distrib(gen);
        uint64_t leastSignificantBits = distrib(gen);

        mostSignificantBits &= 0xFFFFFFFFFFFF0FFFULL;
        mostSignificantBits |= 0x0000000000004000ULL;

        leastSignificantBits &= 0x3FFFFFFFFFFFFFFFULL;
        leastSignificantBits |= 0x8000000000000000ULL;

        return Util::UUID{ mostSignificantBits, leastSignificantBits };
    };
};