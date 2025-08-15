#include "MovePlayerPacket.hpp"
void MovePlayerPacket::read(BinaryStream& stream)
{
    this->actorRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);
    this->position = stream.readVec3();
    this->rotation = stream.readVec2();
    this->yHeadRotation = stream.read<float>();
    this->positionMode = static_cast<PositionMode>(stream.readByte());
    this->isOnGround = stream.readBoolean();
    this->ridingRuntimeId = BinaryStream::serialize<ActorRuntimeId>::read(stream);

    if (this->positionMode == PositionMode::Teleport)
    {
        this->teleportCause = static_cast<TeleportationCause>(stream.readInt());
        this->sourceActorType = static_cast<ActorType>(stream.readInt());
    };

    this->tick = stream.readUnsignedVarLong();
};

void MovePlayerPacket::write(BinaryStream& stream)
{
    BinaryStream::serialize<ActorRuntimeId>::write(this->actorRuntimeId, stream);
    stream.writeVec3(this->position);
    stream.writeVec2(this->rotation);
    stream.write<float>(this->yHeadRotation);
    stream.writeByte(static_cast<uint8_t>(this->positionMode));
    stream.writeBoolean(this->isOnGround);
    BinaryStream::serialize<ActorRuntimeId>::write(this->ridingRuntimeId, stream);

    if (this->positionMode == PositionMode::Teleport)
    {
        stream.writeInt(static_cast<int>(this->teleportCause));
        stream.writeInt(static_cast<int>(this->sourceActorType));
    };

    stream.writeUnsignedVarLong(this->tick);
};