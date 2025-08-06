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
    std::string mName;
    MinecraftPacketIds mPacketId;
    SubClientId mSubClientId = SubClientId::PrimaryClient;

protected:
    std::chrono::high_resolution_clock::time_point mCreatedTimepoint;

public:
    virtual ~Packet() = default;

    Packet(std::string  name, const MinecraftPacketIds packetId) :
        mName(std::move(name)),
        mPacketId(packetId),
        mCreatedTimepoint(std::chrono::high_resolution_clock::now()) {};

    const std::string& getName() const { return this->mName; };
    MinecraftPacketIds getId() const { return this->mPacketId; };

    void setSubClientId(const SubClientId subClientId) { this->mSubClientId = subClientId; };
    SubClientId getSubClientId() const { return this->mSubClientId; };

    virtual void read(BinaryStream&) = 0;
    virtual void write(BinaryStream&) = 0;
};

#endif // !PACKET_HPP