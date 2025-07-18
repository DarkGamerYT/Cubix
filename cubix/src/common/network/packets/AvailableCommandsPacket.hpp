#pragma once
#include "../Packet.hpp"

#include "../../registry/CommandRegistry.hpp"

class AvailableCommandsPacket : public Packet
{
public:
    AvailableCommandsPacket()
        : Packet("AvailableCommandsPacket", MinecraftPacketIds::AvailableCommands) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;

private:
    void writeCommands(BinaryStream&);
    void writeParameters(BinaryStream&, const std::vector<CommandParameter>&);
};