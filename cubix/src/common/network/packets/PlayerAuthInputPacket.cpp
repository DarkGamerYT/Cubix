#include "PlayerAuthInputPacket.hpp"

void PlayerAuthInputPacket::read(BinaryStream& stream)
{
    this->rotation = stream.readVec2();
    this->position = stream.readVec3();
    this->moveVector = stream.readVec2();
    this->headRotation = stream.read<float>();

    constexpr int numActions = static_cast<int>(AuthInputData::Count);
    const auto& bitset = BigUInt128::readUnsignedBigVarInt(stream, numActions);
    for (int i = 0; i < numActions; ++i) {
        if (!bitset.testBit(i))
            continue;

        this->inputData.emplace_back(static_cast<AuthInputData>(i));
    };

    this->inputMode = static_cast<InputMode>(stream.readUnsignedVarInt());
    this->playMode = static_cast<PlayMode>(stream.readUnsignedVarInt());
    this->interactionModel = static_cast<InteractionModel>(stream.readUnsignedVarInt());

    this->interactRotation = stream.readVec2();
    this->tick = stream.readUnsignedVarLong();
    this->posDelta = stream.readVec3();

    if (std::ranges::find(this->inputData, AuthInputData::PerformItemStackRequest) != this->inputData.end())
    {
        this->itemStackRequest = std::make_unique<ItemStackRequestData>(
            BinaryStream::serialize<ItemStackRequestData>::read(stream));
    };

    if (std::ranges::find(this->inputData, AuthInputData::PerformBlockActions) != this->inputData.end())
    {
        const int32_t size = stream.readSignedVarInt();
        for (int32_t i = 0; i < size; ++i)
        {
            this->blockActionData.emplace_back(
                BinaryStream::serialize<PlayerBlockActionData>::read(stream));
        };
    };

    if (std::ranges::find(this->inputData, AuthInputData::IsInClientPredictedVehicle) != this->inputData.end())
    {
        this->vehicleRotation = stream.readVec2();
        this->predictedVehicle = BinaryStream::serialize<ActorUniqueId>::read(stream);
    };

    this->analogMoveVector = stream.readVec2();
    this->cameraOrientation = stream.readVec3();
    this->rawMoveVector = stream.readVec2();
};

void PlayerAuthInputPacket::write(BinaryStream& stream)
{

};