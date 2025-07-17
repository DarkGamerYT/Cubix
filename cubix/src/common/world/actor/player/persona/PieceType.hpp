#ifndef PIECETYPE_HPP
#define PIECETYPE_HPP

#include <string>

namespace persona
{
     enum class PieceType {
        Unknown       = 0,
        Skeleton      = 1,
        Body          = 2,
        Skin          = 3,
        Bottom        = 4,
        Feet          = 5,
        Dress         = 6,
        Top           = 7,
        HighPants     = 8,
        Hands         = 9,
        Outerwear     = 10,
        FacialHair    = 11,
        Mouth         = 12,
        Eyes          = 13,
        Hair          = 14,
        Hood          = 15,
        Back          = 16,
        FaceAccessory = 17,
        Head          = 18,
        Legs          = 19,
        LeftLeg       = 20,
        RightLeg      = 21,
        Arms          = 22,
        LeftArm       = 23,
        RightArm      = 24,
        Capes         = 25,
        ClassicSkin   = 26,
        Emote         = 27,
        Unsupported   = 28
     };

    inline PieceType getPieceType(const std::string& piece) {
        if (piece == "persona_skeleton")
            return PieceType::Skeleton;
        else if (piece == "persona_skin")
            return PieceType::Skin;
        else if (piece == "persona_body")
            return PieceType::Body;
        else if (piece == "persona_mouth")
            return PieceType::Mouth;
        else if (piece == "persona_hair")
            return PieceType::Hair;
        else if (piece == "persona_eyes")
            return PieceType::Eyes;
        else if (piece == "persona_hands")
            return PieceType::Hands;
        else if (piece == "persona_feet")
            return PieceType::Feet;
        else if (piece == "persona_capes")
            return PieceType::Capes;
        else if (piece == "persona_top")
            return PieceType::Top;
        else if (piece == "persona_bottom")
            return PieceType::Bottom;

        return PieceType::Unknown;
    };

    inline std::string getPieceType(PieceType piece) {
        switch (piece)
        {
            case PieceType::Skeleton: return "persona_skeleton";
            case PieceType::Skin: return "persona_skin";
            case PieceType::Body: return "persona_body";
            case PieceType::Mouth: return "persona_mouth";
            case PieceType::Hair: return "persona_hair";
            case PieceType::Eyes: return "persona_eyes";
            case PieceType::Hands: return "persona_hands";
            case PieceType::Feet: return "persona_feet";
            case PieceType::Capes: return "persona_capes";
            case PieceType::Top: return "persona_top";
            case PieceType::Bottom: return "persona_bottom";
            default:
                return "unknown";
        };
    };
};

#endif //PIECETYPE_HPP
