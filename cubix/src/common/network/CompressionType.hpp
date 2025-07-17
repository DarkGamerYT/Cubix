#pragma once

enum class CompressionType : int
{
    Disabled = -1,
    Zlib     = 0x00,
    Snappy   = 0x01,
    None     = 0xFF
};