#ifndef COMPRESSIONTYPE_HPP
#define COMPRESSIONTYPE_HPP

enum class CompressionType : int
{
    Disabled = -1,
    Zlib     = 0x00,
    Snappy   = 0x01,
    None     = 0xFF
};

#endif // !COMPRESSIONTYPE_HPP