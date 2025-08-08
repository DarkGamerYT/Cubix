#ifndef CONNECTIONREQUEST_HPP
#define CONNECTIONREQUEST_HPP

#include <vector>
#include <string>

#include <rapidjson/document.h>

#include "../../util/math/Color.hpp"
#include "../../util/StringUtils.hpp"
#include "../../util/Base64.hpp"
#include "../../util/Logger.hpp"
#include "../../util/UUID.hpp"

class ConnectionRequest
{
private:
    bool mIsValid = false;
    std::string mTitleId;
    std::string mDisplayName;
    std::string mXuid;
    Util::UUID mIdentity{ 0, 0 };
    int64_t issueUnixTime = -1;

    std::string mRawHeader;
    rapidjson::Document mHeader;
    std::string mRawData;
    rapidjson::Document mData;
    std::string mSignature;

public:
    std::string mRawToken;

public:
    explicit ConnectionRequest(const std::string& rawToken);

    bool isValid() const { return this->mIsValid; };
    bool verify(const std::vector<std::string>&);

    const rapidjson::Value& data() const { return this->mData; };

    std::string getPlayFabId() const {
        return this->mData["PlayFabId"].GetString();
    };
    std::string getDeviceId() const {
        return this->mData["DeviceId"].GetString();
    };
    int getBuildPlatform() const {
        return this->mData["DeviceOS"].GetInt();
    };
    int getPlatformType() const {
        return this->mData["PlatformType"].GetInt();
    };
    int64_t getClientRandomId() const {
        return this->mData["ClientRandomId"].GetInt64();
    };
    int getGraphicsMode() const {
        return this->mData["GraphicsMode"].GetInt();
    };
    std::string getThirdPartyName() const {
        return this->mData["ThirdPartyName"].GetString();
    };
    //const std::string& getPlatformId() const;
    //const std::string& getPlatformOnlineId() const;
    //const std::string& getTenantId() const;

    const Util::UUID& getIdentity() const { return this->mIdentity; };
    const std::string& getDisplayName() const { return this->mDisplayName; };
    const std::string& getXuid() const { return this->mXuid; };
    const std::string& getTitleId() const { return this->mTitleId; };

    uint16_t getMaxRenderDistance() const {
        return this->mData["MaxViewDistance"].GetInt();
    };

    //bool isThirdPartyNameOnly() const;
    bool isEditorMode() const {
        return this->mData["IsEditorMode"].GetBool();
    };
    bool isEduMode() const {
        if (!this->mData.HasMember("EduMode") || !this->mData["EduMode"].IsBool())
            return false;

        return this->mData["EduMode"].GetBool();
    };
};

#endif // !CONNECTIONREQUEST_HPP