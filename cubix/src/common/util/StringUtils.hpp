#ifndef STRINGUTIL_HPP
#define STRINGUTIL_HPP

#include <algorithm>
#include <cctype>
#include <string_view>
#include <cstring>
#include <string>
#include <vector>

namespace Util
{
    int32_t hashCode(const std::string_view&);
    bool isInteger(const std::string&);
    bool isNumber(const std::string&);
    std::string toLower(const std::string&);
    std::vector<std::string> splitString(const std::string&, const char* delimiters);
    std::string& stringTrim(std::string&, const char* t);
    std::string replace(const std::string&, const std::string& replace, const std::string& replacement);
};

#endif // !STRINGUTIL_HPP