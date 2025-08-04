#pragma once
#include "../Packet.hpp"
#include "../../server/commands/CommandOrigin.hpp"

class CommandRequestPacket final : public Packet
{
public:
    std::string command;
    std::unique_ptr<CommandOrigin> commandOrigin;
    bool isInternalSource = true;
    int32_t version = -1;

public:
    CommandRequestPacket()
        : Packet("CommandRequestPacket", MinecraftPacketIds::CommandRequest) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
