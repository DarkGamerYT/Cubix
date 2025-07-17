#pragma once
enum class TransportLayer : int {
    RakNet    = 0,
    NetherNet = 1 << 0,
    Unknown   = 1 << 1,
    Default   = 0
};