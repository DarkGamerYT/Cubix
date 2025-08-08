#pragma once
#include "../Packet.hpp"

#include "../../registry/CommandRegistry.hpp"

class AvailableCommandsPacket final : public Packet
{
public:
    AvailableCommandsPacket()
        : Packet("AvailableCommandsPacket", MinecraftPacketIds::AvailableCommands) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;

private:
    void writeCommands(BinaryStream&) const;

    static void writeParameters(BinaryStream&, const std::vector<CommandParameter>&);
};