#ifndef NETWORKIDENTIFIER_HPP
#define NETWORKIDENTIFIER_HPP

#include <cstdint>
#include <iomanip>
#include <sstream>

#include "../../../src-deps/RakNet/Source/RakNetTypes.h"

class NetworkIdentifier
{
public:
    enum class Type : uint8_t {
        RakNet = 0,
        NetherNet = 1,
        Invalid = 2
    };
public:
    uint64_t m_NetherNetId = 0;
    RakNet::RakNetGUID m_Guid = RakNet::UNASSIGNED_RAKNET_GUID;
    NetworkIdentifier::Type m_Type = NetworkIdentifier::Type::Invalid;

public:
    NetworkIdentifier() {};

    explicit NetworkIdentifier(const uint64_t netherNetId)
        : m_NetherNetId(netherNetId), m_Type(NetworkIdentifier::Type::NetherNet) {};

    explicit NetworkIdentifier(RakNet::RakNetGUID const& rakId)
        : m_Guid(rakId), m_Type(NetworkIdentifier::Type::RakNet) {};

    std::string getCorrelationId() const;
    uint64_t getHash() const;
    bool isUnassigned() const {
        switch (this->m_Type)
        {
            case NetworkIdentifier::Type::Invalid:
                return true;
            case NetworkIdentifier::Type::NetherNet:
                return this->m_NetherNetId == 0;
            case NetworkIdentifier::Type::RakNet:
                return this->m_Guid == RakNet::UNASSIGNED_RAKNET_GUID;
        };

        return true;
    };

    bool operator==(NetworkIdentifier const& other) const {
        if (this->m_Type != other.m_Type)
            return false;

        return this->m_Guid == other.m_Guid || this->m_NetherNetId == other.m_NetherNetId;
    };
    bool operator!=(NetworkIdentifier const& other) const { return !(*this == other); };

    bool operator<(NetworkIdentifier const& other) const {
        if (this->m_Type != other.m_Type)
            return this->m_Type < other.m_Type;

        return this->m_Guid < other.m_Guid && this->m_NetherNetId < other.m_NetherNetId;
    };
    bool operator>(NetworkIdentifier const& other) const { return other < *this; };

public:
    static std::string calculateCorrelationId(uint64_t netherNetId);
    static std::string calculateCorrelationId(RakNet::RakNetGUID const& rakId);
};

template <>
struct std::hash<NetworkIdentifier> {
    size_t operator()(const NetworkIdentifier& id) const noexcept {
        const size_t h1 = std::hash<decltype(id.m_Type)>{}(id.m_Type);
        const size_t h2 = std::hash<decltype(id.m_Guid.g)>{}(id.m_Guid.g);
        const size_t h3 = std::hash<decltype(id.m_NetherNetId)>{}(id.m_NetherNetId);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    };
};;

#endif // !NETWORKIDENTIFIER_HPP
