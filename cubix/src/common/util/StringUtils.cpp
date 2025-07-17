#include "StringUtils.hpp"
namespace Util
{
    int32_t hashCode(const std::string_view& str)
    {
        int32_t hash = 0;
        for (const char c : str)
            hash = c + 31 * hash;

        return hash;
    };

    std::string toLower(const std::string& value)
    {
        std::string out = value;
        std::ranges::transform(
            out, out.begin(),
            [](unsigned char c) { return std::tolower(c); }
        );

        return out;
    };

    std::vector<std::string> splitString(const std::string& value, const char* delimiters)
    {
        std::vector<std::string> result;
        size_t start = 0;
        size_t end = value.find_first_of(delimiters);

        while (end != std::string::npos)
        {
            if (end > start)
                result.emplace_back(value.substr(start, end - start));

            start = end + 1;
            end = value.find_first_of(delimiters, start);
        };

        if (start < value.size())
            result.emplace_back(value.substr(start));

        return result;
    };

    std::string& stringTrim(std::string& str, const char* t)
    {
        str.erase(0, str.find_first_not_of(t));
        return str;
    };

    std::string replace(const std::string& value, const std::string& replace, const std::string& replacement)
    {
        std::string out = value;
        size_t pos = 0;
        while ((pos = out.find(replace, pos)) != std::string::npos) {
            out.replace(pos, replace.length(), replacement);
            pos += replacement.length();
        };

        return out;
    };
};