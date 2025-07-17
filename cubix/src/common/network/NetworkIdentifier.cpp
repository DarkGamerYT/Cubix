#include "NetworkIdentifier.hpp"
uint64_t NetworkIdentifier::getHash() const
{
    switch (this->m_Type)
    {
        case NetworkIdentifier::Type::RakNet:
            return this->m_Guid.g;
        case NetworkIdentifier::Type::NetherNet:
            return this->m_NetherNetId;
        default: break;
    };

    return -1;
};

std::string NetworkIdentifier::getCorrelationId() const
{
    std::ostringstream stream;
    switch (this->m_Type)
    {
        case NetworkIdentifier::Type::RakNet:
        {
            stream << "<raknet>";
            stream << NetworkIdentifier::calculateCorrelationId(this->m_Guid);
            break;
        };
        case NetworkIdentifier::Type::NetherNet:
        {
            stream << "<nethernet>";
            stream << NetworkIdentifier::calculateCorrelationId(this->m_NetherNetId);
            break;
        };
        default:
        {
            stream << "<invalid>";
            stream << "0000-0000-0000-0000";
            break;
        };
    };

    return stream.str();
};

std::string NetworkIdentifier::calculateCorrelationId(const uint64_t netherNetId)
{
    std::ostringstream stream;

    stream << std::hex << std::setfill('0')
        << std::setw(4) << ((netherNetId >> 48) & 0xFFFF) << "-"
        << std::setw(4) << ((netherNetId >> 32) & 0xFFFF) << "-"
        << std::setw(4) << ((netherNetId >> 16) & 0xFFFF) << "-"
        << std::setw(4) << (netherNetId & 0xFFFF);

    return stream.str();
};

std::string NetworkIdentifier::calculateCorrelationId(RakNet::RakNetGUID const& rakGuid)
{
    const uint64_t rakId = rakGuid.g;
    std::ostringstream stream;

    stream << std::hex << std::setfill('0')
        << std::setw(4) << ((rakId >> 48) & 0xFFFF) << "-"
        << std::setw(4) << ((rakId >> 32) & 0xFFFF) << "-"
        << std::setw(4) << ((rakId >> 16) & 0xFFFF) << "-"
        << std::setw(4) << (rakId & 0xFFFF);

    return stream.str();
};