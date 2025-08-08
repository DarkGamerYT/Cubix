#pragma once
#include "../Packet.hpp"
#include "../../input/InputMode.hpp"
#include "../../input/InteractionModel.hpp"
#include "../../input/PlayMode.hpp"
#include "../../entity/PlayerBlockActionData.hpp"

#include "../../util/BigUInt128.hpp"
#include "../../world/inventory/network/ItemStackRequestData.hpp"

#include "types/AuthInputData.hpp"

class PlayerAuthInputPacket final : public Packet
{
public:
    Vec2 rotation;
    Vec3 position;
    Vec2 moveVector;
    float headRotation;
    std::vector<AuthInputData> inputData;
    InputMode inputMode;
    PlayMode playMode;
    InteractionModel interactionModel;
    Vec2 interactRotation;
    uint64_t tick;
    Vec3 posDelta;

    std::unique_ptr<ItemStackRequestData> itemStackRequest;
    std::vector<PlayerBlockActionData> blockActionData;
    Vec2 vehicleRotation;
    int64_t predictedVehicle;

    Vec2 analogMoveVector;
    Vec3 cameraOrientation;
    Vec2 rawMoveVector;

public:
    PlayerAuthInputPacket()
        : Packet(
            "PlayerAuthInputPacket",
            MinecraftPacketIds::PlayerAuthInputPacket) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};