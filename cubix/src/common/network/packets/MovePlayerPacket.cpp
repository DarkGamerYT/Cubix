#include "MovePlayerPacket.hpp"
void MovePlayerPacket::read(BinaryStream& stream)
{
    this->actorRuntimeId = stream.readSignedVarLong();
    this->position = stream.readVec3();
    this->rotation = stream.readVec2();
    this->yHeadRotation = stream.readUnsignedInt();
    this->positionMode = static_cast<PositionMode>(stream.readByte());
    this->isOnGround = stream.readBoolean();
    this->ridingRuntimeId = stream.readSignedVarLong();

    if (this->positionMode == PositionMode::Teleport)
    {
        this->teleportCause = static_cast<TeleportationCause>(stream.readInt());
        this->sourceActorType = static_cast<ActorType>(stream.readInt());
    };

    this->tick = stream.readUnsignedVarLong();
};

void MovePlayerPacket::write(BinaryStream& stream)
{
    stream.writeSignedVarLong(this->actorRuntimeId);
    stream.writeVec3(this->position);
    stream.writeVec2(this->rotation);
    stream.writeUnsignedInt(static_cast<uint32_t>(this->yHeadRotation));
    stream.writeByte(static_cast<uint8_t>(this->positionMode));
    stream.writeBoolean(this->isOnGround);
    stream.writeSignedVarLong(this->ridingRuntimeId);

    if (this->positionMode == PositionMode::Teleport)
    {
        stream.writeInt(static_cast<int>(this->teleportCause));
        stream.writeInt(static_cast<int>(this->sourceActorType));
    };

    stream.writeUnsignedVarLong(this->tick);
};