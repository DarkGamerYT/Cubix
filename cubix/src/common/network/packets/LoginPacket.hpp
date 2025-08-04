#pragma once
#include "../Packet.hpp"
#include "../ConnectionRequest.hpp"

class LoginPacket final : public Packet
{
public:
    int protocol = SharedConstants::NetworkProtocolVersion;
    std::vector<std::string> chains;
    std::unique_ptr<ConnectionRequest> connectionRequest;

public:
    LoginPacket()
        : Packet("LoginPacket", MinecraftPacketIds::Login) {};

    void read(BinaryStream& stream) override;
    void write(BinaryStream& stream) override;
};