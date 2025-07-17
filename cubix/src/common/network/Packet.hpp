#ifndef PACKET_HPP
#define PACKET_HPP

#include <chrono>
#include <string>
#include <utility>

#include "../../../src-deps/RakNet/Source/PacketPriority.h"
#include "../SubClientId.hpp"
#include "../util/BinaryStream.hpp"

#include "PacketIds.hpp"

class Packet
{
private:
    std::string m_Name;
    MinecraftPacketIds m_PacketId;
    SubClientId m_SubClientId = SubClientId::PrimaryClient;

protected:
    std::chrono::high_resolution_clock::time_point m_CreatedTimepoint;

public:
    virtual ~Packet() = default;

    Packet(std::string  name, const MinecraftPacketIds packetId)
        : m_Name(std::move(name)),
        m_PacketId(packetId),
        m_CreatedTimepoint(std::chrono::high_resolution_clock::now()) {};

    const std::string& getName() const { return this->m_Name; };
    MinecraftPacketIds getId() const { return this->m_PacketId; };

    void setSubClientId(const SubClientId subClientId) { this->m_SubClientId = subClientId; };
    SubClientId getSubClientId() const { return this->m_SubClientId; };

    virtual void read(BinaryStream&) = 0;
    virtual void write(BinaryStream&) = 0;
};

#endif // !PACKET_HPP