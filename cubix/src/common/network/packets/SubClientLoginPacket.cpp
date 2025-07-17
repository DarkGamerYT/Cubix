#include "SubClientLoginPacket.hpp"
//#include <rapidjson/writer.h>
//#include <rapidjson/document.h>

#include "../../util/Logger.hpp"

void SubClientLoginPacket::read(BinaryStream& stream)
{
    uint32_t remainingDataLength = stream.readUnsignedVarInt();

    {
        // Get chains string
        const uint32_t authenticationLength = stream.readUnsignedInt();
        if (authenticationLength > 3145728)
            return;

        std::string authenticationString;
        authenticationString.resize(authenticationLength);
        {
            const uint8_t* ptr = stream.readBytes(authenticationLength);
            std::memcpy(authenticationString.data(), ptr, authenticationLength);
        };

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
        const uint32_t tokenLength = stream.readUnsignedInt();
        if (tokenLength > 52428800)
            return;

        std::string token;
        token.resize(tokenLength);
        {
            const uint8_t* ptr = stream.readBytes(tokenLength);
            std::memcpy(token.data(), ptr, tokenLength);
        };

        this->connectionRequest = std::make_unique<ConnectionRequest>(token);
    };
};

void SubClientLoginPacket::write(BinaryStream& stream)
{

};