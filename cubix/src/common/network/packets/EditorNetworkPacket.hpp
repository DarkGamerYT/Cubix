#pragma once
#include "../Packet.hpp"
#include "../../nbt/NbtIo.hpp"

class EditorNetworkPacket : public Packet
{
public:
    bool routeToManager;
    Nbt::CompoundTag payload;

public:
    EditorNetworkPacket()
        : Packet("EditorNetworkPacket", MinecraftPacketIds::EditorNetworkPacket) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};