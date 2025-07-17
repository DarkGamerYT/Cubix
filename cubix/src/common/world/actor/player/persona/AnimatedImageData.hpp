#ifndef ANIMATEDIMAGEDATA_HPP
#define ANIMATEDIMAGEDATA_HPP

#include "AnimatedTextureType.hpp"
#include "AnimationExpression.hpp"
#include "../../../../util/Image.hpp"

namespace persona
{
    struct AnimatedImageData {
        AnimatedTextureType type;
        AnimationExpression animationExpression;
        Util::Image         image;
        float               frames;
    };
}

#endif //ANIMATEDIMAGEDATA_HPP
