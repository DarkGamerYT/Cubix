#include "SerializedSkin.hpp"

SerializedSkin::SerializedSkin(const std::unique_ptr<ConnectionRequest>& request) {
    this->m_playFabId = request->getPlayFabId();

    const auto& data = request->data();
    this->m_fullId = Json::getString(data, "SkinId");
    this->m_capeId = Json::getString(data, "CapeId");
    this->m_id = m_fullId.substr(0, m_fullId.size() - m_capeId.size());

    {
        // Skin Image
        this->m_skinImage.height = Json::getInt(data, "SkinImageHeight");
        this->m_skinImage.width = Json::getInt(data, "SkinImageWidth");

        const auto& decodedSkin = Util::Base64::decode(
            Json::getString(data, "SkinData"));

        this->m_skinImage.data = std::vector<uint8_t>(
            decodedSkin.begin(), decodedSkin.end());
    };

    {
        // Cape Image
        this->m_capeImage.height = Json::getInt(data, "CapeImageHeight");
        this->m_capeImage.width = Json::getInt(data, "CapeImageWidth");

        const auto& decodedCape = Util::Base64::decode(
            Json::getString(data, "CapeData"));

        this->m_capeImage.data = std::vector<uint8_t>(
            decodedCape.begin(), decodedCape.end());
    };

    this->m_armSize = persona::getArmSize(Json::getString(data, "ArmSize"));
    this->m_skinColor = Util::Color::fromHexString(Json::getString(data, "SkinColor"));

    {
        const auto& tintColors = Json::getArray(data, "PieceTintColors");
        for (const auto& tintColor : tintColors)
        {
            if (!tintColor.IsObject())
                throw std::exception("Expected tint color to be an object");

            const auto& colors = Json::getArray(tintColor, "Colors");

            TintColorMap colorMap;
            for (size_t i = 0; i < colors.Capacity(); ++i)
            {
                if (!colors[i].IsString())
                    throw std::exception("Json: Expected a string value");

                colorMap[i] = Util::Color::fromHexString(colors[i].GetString());
            };

            const auto& pieceType = Json::getString(tintColor, "PieceType");
            this->m_pieceTintColors.emplace(
                persona::getPieceType(pieceType), colorMap);
        };
    };

    {
        const auto& animatedImages = Json::getArray(data, "AnimatedImageData");
        for (const auto& animatedImage : animatedImages)
        {
            if (!animatedImage.IsObject())
                throw std::exception("Expected animated image to be an object");

            Util::Image image{};
            {
                image.height = Json::getInt(animatedImage, "ImageHeight");
                image.width = Json::getInt(animatedImage, "ImageWidth");

                const auto& decodedImage = Util::Base64::decode(
                    Json::getString(animatedImage, "Image"));

                image.data = std::vector<uint8_t>(
                    decodedImage.begin(), decodedImage.end());
            };

            const auto& type = Json::getInt(animatedImage, "Type");
            const auto& expression = Json::getInt(animatedImage, "AnimationExpression");
            const auto& frames = Json::getFloat(animatedImage, "Frames");
            this->m_skinAnimatedImages.emplace_back(
                static_cast<persona::AnimatedTextureType>(type),
                static_cast<persona::AnimationExpression>(expression),
                image, frames);
        };
    };

    this->m_isTrusted = Json::getBoolean(data, "TrustedSkin");
    this->m_isPremium = Json::getBoolean(data, "PremiumSkin");
    this->m_isPersona = Json::getBoolean(data, "PersonaSkin");
    this->m_isCapeOnClassicSkin = Json::getBoolean(data, "CapeOnClassicSkin");
    //this->m_isPrimaryUser = true;
    try {
        this->m_overridesPlayerAppearance = Json::getBoolean(data, "OverrideSkin");
    }
    catch (...)
    {
        this->m_overridesPlayerAppearance = false;
    }
};

void SerializedSkin::read(BinaryStream& stream) {
    this->m_id = stream.readString();
    this->m_playFabId = stream.readString();
    this->m_resourcePatch.Parse(stream.readString().c_str());
    if (this->m_resourcePatch.HasParseError())
        throw std::exception("Invalid resource patch");

    {
        this->m_skinImage.width = stream.readUnsignedInt();
        this->m_skinImage.height = stream.readUnsignedInt();

        const auto& skinImage = stream.readString();
        this->m_skinImage.data = std::vector<uint8_t>(skinImage.begin(), skinImage.end());
    };

    const uint32_t animatedImages = stream.readUnsignedInt();
    for (uint32_t i = 0; i < animatedImages; i++)
    {
        Util::Image image{};
        {
            image.width = stream.readUnsignedInt();
            image.height = stream.readUnsignedInt();

            const auto& animatedImage = stream.readString();
            image.data = std::vector<uint8_t>(animatedImage.begin(), animatedImage.end());
        };

        const auto& type = stream.readUnsignedInt();
        const auto& frames = static_cast<float>(stream.readUnsignedInt());
        const auto& expression = stream.readUnsignedInt();
        this->m_skinAnimatedImages.emplace_back(
            static_cast<persona::AnimatedTextureType>(type),
            static_cast<persona::AnimationExpression>(expression),
            image, frames);
    };

    {
        this->m_capeImage.width = stream.readUnsignedInt();
        this->m_capeImage.height = stream.readUnsignedInt();

        const auto& capeImage = stream.readString();
        this->m_capeImage.data = std::vector<uint8_t>(capeImage.begin(), capeImage.end());
    };

    this->m_geometryData.Parse(stream.readString().c_str());
    if (this->m_geometryData.HasParseError())
        throw std::exception("Invalid geometry data");

    this->m_geometryMinEngineVersion = stream.readString();
    this->m_animationData = stream.readString();
    this->m_capeId = stream.readString();
    this->m_fullId = stream.readString();
    this->m_armSize = persona::getArmSize(stream.readString());
    this->m_skinColor = Util::Color::fromHexString(stream.readString());

    const uint32_t piecesSize = stream.readUnsignedInt();
    for (uint32_t i = 0; i < piecesSize; i++)
    {
        const auto& pieceId = stream.readString();
        const auto& pieceType = stream.readString();
        const auto& packId = stream.readString();
        const auto& isDefault = stream.readBoolean();
        const auto& productId = stream.readString();

        this->m_personaPieces.emplace_back(
            pieceId,
            persona::getPieceType(pieceType),
            Util::UUID::fromString(packId),
            isDefault, productId);
    };

    const uint32_t tintsSize = stream.readUnsignedInt();
    for (uint32_t i = 0; i < tintsSize; i++)
    {
        const auto& pieceType = stream.readString();
        TintColorMap colorMap;

        const uint32_t colorsSize = stream.readUnsignedInt();
        for (uint32_t j = 0; j < colorsSize; j++)
            colorMap[j] = Util::Color::fromHexString(stream.readString());

        this->m_pieceTintColors.emplace(
            persona::getPieceType(pieceType), colorMap);
    };

    this->m_isPremium = stream.readBoolean();
    this->m_isPersona = stream.readBoolean();
    this->m_isCapeOnClassicSkin = stream.readBoolean();
    this->m_isPrimaryUser = stream.readBoolean();
    this->m_overridesPlayerAppearance = stream.readBoolean();
};

void SerializedSkin::write(BinaryStream& stream) {
    stream.writeString(this->m_id);
    stream.writeString(this->m_playFabId);
    stream.writeString(Json::toString(this->m_resourcePatch));

    {
        stream.writeUnsignedInt(this->m_skinImage.width);
        stream.writeUnsignedInt(this->m_skinImage.height);

        const auto& data = this->m_skinImage.data;
        stream.writeString(
            std::string(data.begin(), data.end()));
    };

    stream.writeUnsignedInt(static_cast<uint32_t>(this->m_skinAnimatedImages.size()));
    for (const auto& animatedImage : this->m_skinAnimatedImages)
    {
        stream.writeUnsignedInt(animatedImage.image.width);
        stream.writeUnsignedInt(animatedImage.image.height);

        const auto& data = animatedImage.image.data;
        stream.writeString(
            std::string(data.begin(), data.end()));

        stream.writeUnsignedInt(static_cast<uint32_t>(animatedImage.type));
        stream.writeUnsignedInt(static_cast<uint32_t>(animatedImage.frames));
        stream.writeUnsignedInt(static_cast<uint32_t>(animatedImage.animationExpression));
    };

    {
        stream.writeUnsignedInt(this->m_capeImage.width);
        stream.writeUnsignedInt(this->m_capeImage.height);

        const auto& data = this->m_capeImage.data;
        stream.writeString(
            std::string(data.begin(), data.end()));
    };

    stream.writeString(Json::toString(this->m_geometryData));
    stream.writeString(this->m_geometryMinEngineVersion);
    stream.writeString(this->m_animationData);
    stream.writeString(this->m_capeId);
    stream.writeString(this->m_fullId);
    stream.writeString(persona::getArmSize(this->m_armSize));
    stream.writeString(this->m_skinColor.toHexString());

    stream.writeUnsignedInt(static_cast<uint32_t>(this->m_personaPieces.size()));
    for (const auto& personaPiece : this->m_personaPieces)
    {
        stream.writeString(personaPiece.pieceId);
        stream.writeString(persona::getPieceType(personaPiece.pieceType));
        stream.writeString(personaPiece.packId.toString());
        stream.writeBoolean(personaPiece.isDefault);
        stream.writeString(personaPiece.productId);
    };

    stream.writeUnsignedInt(static_cast<uint32_t>(this->m_pieceTintColors.size()));
    for (const auto& tintColor : this->m_pieceTintColors)
    {
        stream.writeString(persona::getPieceType(tintColor.first));

        TintColorMap colorMap = tintColor.second;

        stream.writeUnsignedInt(static_cast<uint32_t>(colorMap.size()));
        for (size_t i = 0; i < colorMap.size(); i++)
            stream.writeString(colorMap[i].toHexString());
    };

    stream.writeBoolean(this->m_isPremium);
    stream.writeBoolean(this->m_isPersona);
    stream.writeBoolean(this->m_isCapeOnClassicSkin);
    stream.writeBoolean(this->m_isPrimaryUser);
    stream.writeBoolean(this->m_overridesPlayerAppearance);
};