#pragma once
#include "../Packet.hpp"
#include "../ConnectionRequest.hpp"

class SubClientLoginPacket final : public Packet
{
public:
    std::vector<std::string> chains;
    std::unique_ptr<ConnectionRequest> connectionRequest;

public:
    SubClientLoginPacket()
        : Packet("SubClientLoginPacket", MinecraftPacketIds::SubclientLogin) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};