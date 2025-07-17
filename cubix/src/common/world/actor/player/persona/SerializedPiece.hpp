#ifndef SERIALIZEDPIECE_HPP
#define SERIALIZEDPIECE_HPP

#include "../../../../util/UUID.hpp"

#include "PieceType.hpp"

namespace persona
{
    struct SerializedPiece {
        std::string pieceId;
        PieceType   pieceType;
        Util::UUID  packId;
        bool        isDefault;
        std::string productId;
    };
};

#endif //SERIALIZEDPIECE_HPP
