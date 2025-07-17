#include "ConnectionRequest.hpp"
ConnectionRequest::ConnectionRequest(const std::string& rawToken)
    : mRawToken(rawToken)
{
    const std::vector<std::string>& parts = Util::splitString(rawToken, ".");

    this->mRawHeader = parts[0];
    const std::string& header = Util::Base64::decode(this->mRawHeader);

    this->mHeader.Parse(header.c_str());
    if (this->mHeader.HasParseError() || !this->mHeader.IsObject())
        return;


    this->mRawData = parts[1];
    const std::string& data = Util::Base64::decode(this->mRawData);

    this->mData.Parse(data.c_str());
    if (this->mData.HasParseError() || !this->mData.IsObject())
        return;

    this->mSignature = parts[2];
    this->mIsValid = true;
};

bool ConnectionRequest::verify(const std::vector<std::string>& chains)
{
    for (const std::string& chain : chains)
    {
        const std::vector<std::string>& base = Util::splitString(chain, ".");
        const std::string& header = Util::Base64::decode(base[0]);

        rapidjson::Document headerJson;
        headerJson.Parse(header.c_str());
        if (headerJson.HasParseError())
            return false;

        const std::string& decoded = Util::Base64::decode(base[1]);

        rapidjson::Document bodyJson;
        bodyJson.Parse(decoded.c_str());
        if (bodyJson.HasParseError())
            return false;

        const auto& x5u = headerJson["x5u"].GetString();
        const auto& identityPublicKey = bodyJson["identityPublicKey"].GetString();

        if (bodyJson.HasMember("extraData") && bodyJson["extraData"].IsObject())
        {
            const auto& extraData = bodyJson["extraData"];
            if (bodyJson.HasMember("iat") && bodyJson["iat"].IsInt64())
                this->issueUnixTime = bodyJson["iat"].GetInt64();

            const auto& identity = extraData["identity"].GetString();
            this->mIdentity = Util::UUID::fromString(identity);
            this->mTitleId = extraData["titleId"].GetString();
            this->mDisplayName = extraData["displayName"].GetString();
            this->mXuid = extraData["XUID"].GetString();
        };
    };

    return true;
};