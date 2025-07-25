#ifndef LEVELCHUNKFORMAT_HPP
#define LEVELCHUNKFORMAT_HPP

#include <stdint.h>

enum class LevelChunkFormat : uint8_t {
    V9_00                          = 0,
    V9_02                          = 1,
    V9_05                          = 2,
    V17_0                          = 3,
    V18_0                          = 4,
    VConsole1ToV18_0               = 5,
    V1_2_0                         = 6,
    V1_2_0Bis                      = 7,
    V1_3_0                         = 8,
    V1_8_0                         = 9,
    V1_9_0                         = 10,
    V1_10_0                        = 11,
    V1_11_0                        = 12,
    V1_11_1                        = 13,
    V1_11_2                        = 14,
    V1_12_0                        = 15,
    V1_14_0                        = 16,
    V1_15_0                        = 17,
    V1_16_0                        = 18,
    V1_16_0Bis                     = 19,
    V1_16_100                      = 20,
    V1_16_100Bis                   = 21,
    V1_16_210                      = 22,
    V1_16_300CavesCliffsPart1      = 23,
    V1_16_300CavesCliffsInternalV1 = 24,
    V1_16_300CavesCliffsPart2      = 25,
    V1_16_300CavesCliffsInternalV2 = 26,
    V1_16_300CavesCliffsPart3      = 27,
    V1_16_300CavesCliffsInternalV3 = 28,
    V1_16_300CavesCliffsPart4      = 29,
    V1_16_300CavesCliffsInternalV4 = 30,
    V1_16_300CavesCliffsPart5      = 31,
    V1_16_300CavesCliffsInternalV5 = 32,
    V1_18_0                        = 33,
    V1_18_0Internal                = 34,
    V1_18_1                        = 35,
    V1_18_1Internal                = 36,
    V1_18_2                        = 37,
    V1_18_2Internal                = 38,
    V1_18_3                        = 39,
    V1_18_3IndividualActorStorage  = 40,
    V1_21_4                        = 41
};

#endif // !LEVELCHUNKFORMAT_HPP