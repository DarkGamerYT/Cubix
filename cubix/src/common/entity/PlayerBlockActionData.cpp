#include "PlayerBlockActionData.hpp"
PlayerBlockActionData BinaryStream::serialize<PlayerBlockActionData>::read(BinaryStream& stream) {
    PlayerBlockActionData blockActionData{};

    blockActionData.mAction = static_cast<PlayerActionType>(stream.readSignedVarInt());
    switch (blockActionData.mAction)
    {
        case PlayerActionType::PredictDestroyBlock:
        case PlayerActionType::StartDestroyBlock:
        case PlayerActionType::AbortDestroyBlock:
        case PlayerActionType::CrackBlock:
        case PlayerActionType::ContinueDestroyBlock: {
            blockActionData.mPosition = stream.readBlockPosition();
            blockActionData.mFacing = stream.readSignedVarInt();
            break;
        };
        default:
            break;
    };

    return blockActionData;
};

void BinaryStream::serialize<PlayerBlockActionData>::write(const PlayerBlockActionData& value, BinaryStream& stream) {
    stream.writeSignedVarInt(static_cast<int32_t>(value.mAction));
    switch (value.mAction)
    {
        case PlayerActionType::PredictDestroyBlock:
        case PlayerActionType::StartDestroyBlock:
        case PlayerActionType::AbortDestroyBlock:
        case PlayerActionType::CrackBlock:
        case PlayerActionType::ContinueDestroyBlock: {
            stream.writeBlockPosition(value.mPosition);
            stream.writeSignedVarInt(value.mFacing);
            break;
        };
        default:
            break;
    };
};