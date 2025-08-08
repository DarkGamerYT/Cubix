#ifndef NETWORKIDENTIFIER_HPP
#define NETWORKIDENTIFIER_HPP

#include <cstdint>
#include <iomanip>
#include <sstream>

#include "../../../../src-deps/RakNet/Source/RakNetTypes.h"

class NetworkIdentifier
{
public:
    enum class Type : uint8_t {
        RakNet = 0,
        NetherNet = 1,
        Invalid = 2
    };
public:
    uint64_t mNetherNetId = 0;
    RakNet::RakNetGUID mGuid = RakNet::UNASSIGNED_RAKNET_GUID;
    NetworkIdentifier::Type mType = NetworkIdentifier::Type::Invalid;

public:
    NetworkIdentifier() = default;

    explicit NetworkIdentifier(const uint64_t netherNetId)
        : mNetherNetId(netherNetId), mType(NetworkIdentifier::Type::NetherNet) {};

    explicit NetworkIdentifier(RakNet::RakNetGUID const& rakId)
        : mGuid(rakId), mType(NetworkIdentifier::Type::RakNet) {};

    std::string getCorrelationId() const;
    uint64_t getHash() const;
    bool isUnassigned() const {
        switch (this->mType)
        {
            case NetworkIdentifier::Type::Invalid:
                return true;
            case NetworkIdentifier::Type::NetherNet:
                return this->mNetherNetId == 0;
            case NetworkIdentifier::Type::RakNet:
                return this->mGuid == RakNet::UNASSIGNED_RAKNET_GUID;
        };

        return true;
    };

    bool operator==(NetworkIdentifier const& other) const {
        if (this->mType != other.mType)
            return false;

        return this->mGuid == other.mGuid || this->mNetherNetId == other.mNetherNetId;
    };
    bool operator!=(NetworkIdentifier const& other) const { return !(*this == other); };

    bool operator<(NetworkIdentifier const& other) const {
        if (this->mType != other.mType)
            return this->mType < other.mType;

        return this->mGuid < other.mGuid && this->mNetherNetId < other.mNetherNetId;
    };
    bool operator>(NetworkIdentifier const& other) const { return other < *this; };

public:
    static std::string calculateCorrelationId(uint64_t netherNetId);
    static std::string calculateCorrelationId(RakNet::RakNetGUID const& rakId);
};

template <>
struct std::hash<NetworkIdentifier> {
    size_t operator()(const NetworkIdentifier& id) const noexcept {
        const size_t h1 = std::hash<decltype(id.mType)>{}(id.mType);
        const size_t h2 = std::hash<decltype(id.mGuid.g)>{}(id.mGuid.g);
        const size_t h3 = std::hash<decltype(id.mNetherNetId)>{}(id.mNetherNetId);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    };
};;

#endif // !NETWORKIDENTIFIER_HPP
