#ifndef STORAGEVERSION_HPP
#define STORAGEVERSION_HPP

enum class StorageVersion : int {
    Unknown = 0,
    OldV1 = 1,
    OldV2 = 2,
    OldV3 = 3,
    LevelDB1 = 4,
    LevelDBSubChunks = 5,
    LevelDBSubChunkRawZip = 6,
    LevelDBPaletted1 = 7,
    LevelDBPalettedMultiBlockStorage = 8,
    LevelDataUpgradedSeed = 9,
    LevelDataStrictSize = 10,
};

#endif // !STORAGEVERSION_HPP