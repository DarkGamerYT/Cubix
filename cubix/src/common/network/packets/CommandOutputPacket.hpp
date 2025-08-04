#pragma once
#include "../Packet.hpp"
#include "../../server/commands/CommandOrigin.hpp"
#include "../../server/commands/CommandOutput.hpp"

class CommandOutputPacket final : public Packet
{
public:
    std::unique_ptr<CommandOrigin> commandOrigin;
    CommandOutput commandOutput;

public:
    CommandOutputPacket()
        : Packet("CommandOutputPacket", MinecraftPacketIds::CommandOutput) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};
