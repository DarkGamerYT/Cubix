#ifndef SERIALIZEDSKIN_HPP
#define SERIALIZEDSKIN_HPP

#include <array>

#include "../../../network/connection/ConnectionRequest.hpp"
#include "../../../util/BinaryStream.hpp"
#include "../../../util/math/Color.hpp"
#include "../../../util/Image.hpp"
#include "../../../util/Json.hpp"

#include "persona/AnimatedImageData.hpp"
#include "persona/ArmSize.hpp"
#include "persona/PieceType.hpp"
#include "persona/SerializedPiece.hpp"

using TintColorMap = std::array<Util::Color, 4>;
class SerializedSkin {
private:
    std::string mId;
    std::string mFullId;
    std::string mPlayFabId;
    std::string mCapeId;
    Util::Image mSkinImage;
    Util::Image mCapeImage;

    rapidjson::Document mResourcePatch;
    rapidjson::Document mGeometryData;
    std::string mGeometryMinEngineVersion;
    std::string mAnimationData;

    persona::ArmSize mArmSize = persona::ArmSize::Wide;
    Util::Color mSkinColor;
    std::unordered_map<persona::PieceType, TintColorMap> mPieceTintColors;
    std::vector<persona::AnimatedImageData> mSkinAnimatedImages;
    std::vector<persona::SerializedPiece> mPersonaPieces;

    bool mIsTrusted = true;
    bool mIsPremium = false;
    bool mIsPersona = false;
    bool mIsCapeOnClassicSkin = false;
    bool mIsPrimaryUser = true;
    bool m_overridesPlayerAppearance = true;

public:
    SerializedSkin() = default;
    explicit SerializedSkin(const std::unique_ptr<ConnectionRequest>&);

    bool isTrusted() const { return this->mIsTrusted; };
    bool isPersona() const { return this->mIsPersona; };

    void read(BinaryStream&);
    void write(BinaryStream&);
};

#endif //SERIALIZEDSKIN_HPP
