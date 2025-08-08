#ifndef SHAREDCONSTANTS_HPP
#define SHAREDCONSTANTS_HPP

#include "GameVersion.hpp"

#include "world/level/chunk/LevelChunkFormat.hpp"
#include "world/level/chunk/SubChunkFormat.hpp"
#include "world/level/storage/StorageVersion.hpp"

class SharedConstants
{
public:
    static constexpr bool IsDebug = (BUILD_TYPE == std::string("Debug"));
    static inline const GameVersion CurrentGameVersion{
        1, 21, 100, 0,
        (PREVIEW_BUILD == std::string("TRUE"))
    };

    static constexpr int MinTickingChunksRadius = 4;
    static constexpr auto CurrentLevelChunkFormat = LevelChunkFormat::V1_21_4;
    static constexpr auto CurrentStorageVersion = StorageVersion::LevelDataStrictSize;
    static constexpr auto CurrentSubChunkFormat = SubChunkFormat::V1_3_0_3;

    static constexpr int NetworkProtocolVersion = 827;
    static constexpr int NetworkMaxPlayers = 30;
    static constexpr uint16_t NetworkDefaultGamePort = 19132;
    static constexpr uint16_t NetworkDefaultGamePortv6 = 19133;
};

#endif // !SHAREDCONSTANTS_HPP