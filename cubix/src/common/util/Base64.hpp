//
//  base64 encoding and decoding with C++.
//  Version: 2.rc.09 (release candidate)
//

#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A

#include <string>

#if __cplusplus >= 201703L
#include <string_view>
#endif  // __cplusplus >= 201703L

namespace Util
{
    namespace Base64
    {
        std::string encode(std::string const& s, bool url = false);
        std::string encode(unsigned char const*, size_t len, bool url = false);
        std::string encode_pem(std::string const& s);
        std::string encode_mime(std::string const& s);

        std::string decode(std::string const& s, bool remove_linebreaks = false);
    };
};

#if __cplusplus >= 201703L
//
// Interface with std::string_view rather than const std::string&
// Requires C++17
// Provided by Yannic Bonenberger (https://github.com/Yannic)
//
namespace Util
{
    namespace Base64
    {
        std::string encode(std::string_view s, bool url = false);
        std::string encode_pem(std::string_view s);
        std::string encode_mime(std::string_view s);

        std::string decode(std::string_view s, bool remove_linebreaks = false);
    };
};
#endif  // __cplusplus >= 201703L

#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */