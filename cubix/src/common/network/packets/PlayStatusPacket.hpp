#pragma once
#include "../Packet.hpp"

enum class PlayStatus
{
    LoginSuccess = 0x00,
    ClientOld = 0x01,
    ServerOld = 0x02,
    PlayerSpawn = 0x03,
    InvalidTenant = 0x04,
    EditionMismatchEduToVanilla = 0x05,
    EditionMismatchVanillaToEdu = 0x06,
    ServerFullSubClient = 0x07,
    EditorMismatchEditorToVanilla = 0x08,
    EditorMismatchVanillaToEditor = 0x09
};

class PlayStatusPacket final : public Packet
{
public:
    PlayStatus status;

public:
    PlayStatusPacket()
        : Packet("PlayStatusPacket", MinecraftPacketIds::PlayStatus) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};