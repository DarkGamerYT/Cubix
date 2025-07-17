#ifndef SERIALIZEDSKIN_HPP
#define SERIALIZEDSKIN_HPP

#include <array>

#include "../../../network/ConnectionRequest.hpp"
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
    std::string m_id;
    std::string m_fullId;
    std::string m_playFabId;
    std::string m_capeId;
    Util::Image m_skinImage;
    Util::Image m_capeImage;

    rapidjson::Document m_resourcePatch;
    rapidjson::Document m_geometryData;
    std::string m_geometryMinEngineVersion;
    std::string m_animationData;

    persona::ArmSize m_armSize = persona::ArmSize::Wide;
    Util::Color m_skinColor;
    std::unordered_map<persona::PieceType, TintColorMap> m_pieceTintColors;
    std::vector<persona::AnimatedImageData> m_skinAnimatedImages;
    std::vector<persona::SerializedPiece> m_personaPieces;

    bool m_isTrusted = true;
    bool m_isPremium = false;
    bool m_isPersona = false;
    bool m_isCapeOnClassicSkin = false;
    bool m_isPrimaryUser = true;
    bool m_overridesPlayerAppearance = true;

public:
    SerializedSkin() = default;
    SerializedSkin(const std::unique_ptr<ConnectionRequest>&);

    bool isTrusted() const { return this->m_isTrusted; };
    bool isPersona() const { return this->m_isPersona; };

    void read(BinaryStream&);
    void write(BinaryStream&);
};

#endif //SERIALIZEDSKIN_HPP
