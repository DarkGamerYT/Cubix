#include "SerializedSkin.hpp"

SerializedSkin::SerializedSkin(const std::unique_ptr<ConnectionRequest>& request) {
    this->mPlayFabId = request->getPlayFabId();

    const auto& data = request->data();
    this->mFullId = Json::getString(data, "SkinId");
    this->mCapeId = Json::getString(data, "CapeId");
    this->mId = mFullId.substr(0, mFullId.size() - mCapeId.size());

    {
        // Skin Image
        this->mSkinImage.height = Json::getInt(data, "SkinImageHeight");
        this->mSkinImage.width = Json::getInt(data, "SkinImageWidth");

        const auto& decodedSkin = Util::Base64::decode(
            Json::getString(data, "SkinData"));

        this->mSkinImage.data = std::vector<uint8_t>(
            decodedSkin.begin(), decodedSkin.end());
    };

    {
        // Cape Image
        this->mCapeImage.height = Json::getInt(data, "CapeImageHeight");
        this->mCapeImage.width = Json::getInt(data, "CapeImageWidth");

        const auto& decodedCape = Util::Base64::decode(
            Json::getString(data, "CapeData"));

        this->mCapeImage.data = std::vector<uint8_t>(
            decodedCape.begin(), decodedCape.end());
    };

    this->mArmSize = persona::getArmSize(Json::getString(data, "ArmSize"));
    this->mSkinColor = Util::Color::fromHexString(Json::getString(data, "SkinColor"));

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
            this->mPieceTintColors.emplace(
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
            this->mSkinAnimatedImages.emplace_back(
                static_cast<persona::AnimatedTextureType>(type),
                static_cast<persona::AnimationExpression>(expression),
                image, frames);
        };
    };

    this->mIsTrusted = Json::getBoolean(data, "TrustedSkin");
    this->mIsPremium = Json::getBoolean(data, "PremiumSkin");
    this->mIsPersona = Json::getBoolean(data, "PersonaSkin");
    this->mIsCapeOnClassicSkin = Json::getBoolean(data, "CapeOnClassicSkin");
    //this->mIsPrimaryUser = true;
    try {
        this->m_overridesPlayerAppearance = Json::getBoolean(data, "OverrideSkin");
    }
    catch (...)
    {
        this->m_overridesPlayerAppearance = false;
    }
};

void SerializedSkin::read(BinaryStream& stream) {
    this->mId = stream.readString<Endianness::NetworkEndian>();
    this->mPlayFabId = stream.readString<Endianness::NetworkEndian>();
    this->mResourcePatch.Parse(stream.readString<Endianness::NetworkEndian>().c_str());
    if (this->mResourcePatch.HasParseError())
        throw std::exception("Invalid resource patch");

    {
        this->mSkinImage.width = stream.readUnsignedInt();
        this->mSkinImage.height = stream.readUnsignedInt();

        const auto& skinImage = stream.readString<Endianness::NetworkEndian>();
        this->mSkinImage.data = std::vector<uint8_t>(skinImage.begin(), skinImage.end());
    };

    const uint32_t animatedImages = stream.readUnsignedInt();
    for (uint32_t i = 0; i < animatedImages; i++)
    {
        Util::Image image{};
        {
            image.width = stream.readUnsignedInt();
            image.height = stream.readUnsignedInt();

            const auto& animatedImage = stream.readString<Endianness::NetworkEndian>();
            image.data = std::vector<uint8_t>(animatedImage.begin(), animatedImage.end());
        };

        const auto& type = stream.readUnsignedInt();
        const auto& frames = static_cast<float>(stream.readUnsignedInt());
        const auto& expression = stream.readUnsignedInt();
        this->mSkinAnimatedImages.emplace_back(
            static_cast<persona::AnimatedTextureType>(type),
            static_cast<persona::AnimationExpression>(expression),
            image, frames);
    };

    {
        this->mCapeImage.width = stream.readUnsignedInt();
        this->mCapeImage.height = stream.readUnsignedInt();

        const auto& capeImage = stream.readString<Endianness::NetworkEndian>();
        this->mCapeImage.data = std::vector<uint8_t>(capeImage.begin(), capeImage.end());
    };

    this->mGeometryData.Parse(stream.readString<Endianness::NetworkEndian>().c_str());
    if (this->mGeometryData.HasParseError())
        throw std::exception("Invalid geometry data");

    this->mGeometryMinEngineVersion = stream.readString<Endianness::NetworkEndian>();
    this->mAnimationData = stream.readString<Endianness::NetworkEndian>();
    this->mCapeId = stream.readString<Endianness::NetworkEndian>();
    this->mFullId = stream.readString<Endianness::NetworkEndian>();
    this->mArmSize = persona::getArmSize(stream.readString<Endianness::NetworkEndian>());
    this->mSkinColor = Util::Color::fromHexString(stream.readString<Endianness::NetworkEndian>());

    const uint32_t piecesSize = stream.readUnsignedInt();
    for (uint32_t i = 0; i < piecesSize; i++)
    {
        const auto& pieceId = stream.readString<Endianness::NetworkEndian>();
        const auto& pieceType = stream.readString<Endianness::NetworkEndian>();
        const auto& packId = stream.readString<Endianness::NetworkEndian>();
        const auto& isDefault = stream.readBoolean();
        const auto& productId = stream.readString<Endianness::NetworkEndian>();

        this->mPersonaPieces.emplace_back(
            pieceId,
            persona::getPieceType(pieceType),
            Util::UUID::fromString(packId),
            isDefault, productId);
    };

    const uint32_t tintsSize = stream.readUnsignedInt();
    for (uint32_t i = 0; i < tintsSize; i++)
    {
        const auto& pieceType = stream.readString<Endianness::NetworkEndian>();
        TintColorMap colorMap;

        const uint32_t colorsSize = stream.readUnsignedInt();
        for (uint32_t j = 0; j < colorsSize; j++)
            colorMap[j] = Util::Color::fromHexString(stream.readString<Endianness::NetworkEndian>());

        this->mPieceTintColors.emplace(
            persona::getPieceType(pieceType), colorMap);
    };

    this->mIsPremium = stream.readBoolean();
    this->mIsPersona = stream.readBoolean();
    this->mIsCapeOnClassicSkin = stream.readBoolean();
    this->mIsPrimaryUser = stream.readBoolean();
    this->m_overridesPlayerAppearance = stream.readBoolean();
};

void SerializedSkin::write(BinaryStream& stream) {
    stream.writeString<Endianness::NetworkEndian>(this->mId);
    stream.writeString<Endianness::NetworkEndian>(this->mPlayFabId);
    stream.writeString<Endianness::NetworkEndian>(Json::toString(this->mResourcePatch));

    {
        stream.writeUnsignedInt(this->mSkinImage.width);
        stream.writeUnsignedInt(this->mSkinImage.height);

        const auto& data = this->mSkinImage.data;
        stream.writeString<Endianness::NetworkEndian>(
            std::string(data.begin(), data.end()));
    };

    stream.writeUnsignedInt(static_cast<uint32_t>(this->mSkinAnimatedImages.size()));
    for (const auto& animatedImage : this->mSkinAnimatedImages)
    {
        stream.writeUnsignedInt(animatedImage.image.width);
        stream.writeUnsignedInt(animatedImage.image.height);

        const auto& data = animatedImage.image.data;
        stream.writeString<Endianness::NetworkEndian>(
            std::string(data.begin(), data.end()));

        stream.writeUnsignedInt(static_cast<uint32_t>(animatedImage.type));
        stream.writeUnsignedInt(static_cast<uint32_t>(animatedImage.frames));
        stream.writeUnsignedInt(static_cast<uint32_t>(animatedImage.animationExpression));
    };

    {
        stream.writeUnsignedInt(this->mCapeImage.width);
        stream.writeUnsignedInt(this->mCapeImage.height);

        const auto& data = this->mCapeImage.data;
        stream.writeString<Endianness::NetworkEndian>(
            std::string(data.begin(), data.end()));
    };

    stream.writeString<Endianness::NetworkEndian>(Json::toString(this->mGeometryData));
    stream.writeString<Endianness::NetworkEndian>(this->mGeometryMinEngineVersion);
    stream.writeString<Endianness::NetworkEndian>(this->mAnimationData);
    stream.writeString<Endianness::NetworkEndian>(this->mCapeId);
    stream.writeString<Endianness::NetworkEndian>(this->mFullId);
    stream.writeString<Endianness::NetworkEndian>(persona::getArmSize(this->mArmSize));
    stream.writeString<Endianness::NetworkEndian>(this->mSkinColor.toHexString());

    stream.writeUnsignedInt(static_cast<uint32_t>(this->mPersonaPieces.size()));
    for (const auto& personaPiece : this->mPersonaPieces)
    {
        stream.writeString<Endianness::NetworkEndian>(personaPiece.pieceId);
        stream.writeString<Endianness::NetworkEndian>(persona::getPieceType(personaPiece.pieceType));
        stream.writeString<Endianness::NetworkEndian>(personaPiece.packId.toString());
        stream.writeBoolean(personaPiece.isDefault);
        stream.writeString<Endianness::NetworkEndian>(personaPiece.productId);
    };

    stream.writeUnsignedInt(static_cast<uint32_t>(this->mPieceTintColors.size()));
    for (const auto& tintColor : this->mPieceTintColors)
    {
        stream.writeString<Endianness::NetworkEndian>(persona::getPieceType(tintColor.first));

        TintColorMap colorMap = tintColor.second;

        stream.writeUnsignedInt(static_cast<uint32_t>(colorMap.size()));
        for (size_t i = 0; i < colorMap.size(); i++)
            stream.writeString<Endianness::NetworkEndian>(colorMap[i].toHexString());
    };

    stream.writeBoolean(this->mIsPremium);
    stream.writeBoolean(this->mIsPersona);
    stream.writeBoolean(this->mIsCapeOnClassicSkin);
    stream.writeBoolean(this->mIsPrimaryUser);
    stream.writeBoolean(this->m_overridesPlayerAppearance);
};