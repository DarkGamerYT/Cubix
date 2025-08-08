#ifndef TRANSPORTLAYER_HPP
#define TRANSPORTLAYER_HPP

enum class TransportLayer : int {
    RakNet    = 0,
    NetherNet = 1 << 0,
    Unknown   = 1 << 1,
    Default   = 0
};

#endif // !TRANSPORTLAYER_HPP