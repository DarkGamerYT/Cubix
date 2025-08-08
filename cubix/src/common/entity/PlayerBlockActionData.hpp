#ifndef PLAYERBLOCKACTIONDATA_HPP
#define PLAYERBLOCKACTIONDATA_HPP

#include "../network/packets/types/PlayerActionType.hpp"
#include "../world/level/BlockPos.hpp"
#include "../util/BinaryStream.hpp"

class PlayerBlockActionData {
    friend struct BinaryStream::serialize<PlayerBlockActionData>;

private:
    PlayerActionType mAction = PlayerActionType::Unknown;
    BlockPos mPosition{};
    int mFacing = 0;

public:
    PlayerBlockActionData() = default;

    PlayerActionType getAction() const { return this->mAction; };
    const BlockPos& getPosition() const { return this->mPosition; };
    int getFacing() const { return this->mFacing; };
};

template <>
struct BinaryStream::serialize<PlayerBlockActionData> {
    static PlayerBlockActionData read(BinaryStream& stream);
    static void write(const PlayerBlockActionData& value, BinaryStream& stream);
};

#endif //PLAYERBLOCKACTIONDATA_HPP
