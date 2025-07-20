#include "LoginPacket.hpp"
//#include <rapidjson/writer.h>
//#include <rapidjson/document.h>

#include "../../util/Logger.hpp"

void LoginPacket::read(BinaryStream& stream)
{
    this->protocol = stream.readInt<Endianness::BigEndian>();

    uint32_t remainingDataLength = stream.readUnsignedVarInt();

    {
        // Get chains string
        std::string authenticationString = stream.readString<Endianness::LittleEndian>();
        if (authenticationString.size() > 3145728)
            return;

        // Parse authentication stuff into JSON
        rapidjson::Document authentication;
        authentication.Parse(authenticationString.c_str());

        if (authentication.HasParseError() || !authentication.IsObject())
            return;

        if (!authentication.HasMember("Certificate") || !authentication["Certificate"].IsString())
            return;

        const auto& certificateString = authentication["Certificate"].GetString();

        // Parse certificate into JSON
        rapidjson::Document certificate;
        certificate.Parse(certificateString);

        if (certificate.HasParseError() || !certificate.IsObject())
            return;

        if (!certificate.HasMember("chain") || !certificate["chain"].IsArray())
            return;

        for (auto& value : certificate["chain"].GetArray())
            this->chains.emplace_back(value.GetString());
    };

    {
        // Get login token string
        const std::string& token = stream.readString<Endianness::LittleEndian>();
        if (token.size() > 52428800)
            return;

        this->connectionRequest = std::make_unique<ConnectionRequest>(token);
    };
};

void LoginPacket::write(BinaryStream& stream)
{

};