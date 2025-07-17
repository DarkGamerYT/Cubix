#ifndef ARMSIZE_HPP
#define ARMSIZE_HPP

namespace persona
{
    enum class ArmSize {
        Slim = 0,
        Wide = 1
    };

    inline std::string getArmSize(const ArmSize size) {
        switch (size)
        {
            case ArmSize::Slim:
                return "slim";
            case ArmSize::Wide:
            default:
                return "wide";
        };
    };

    inline ArmSize getArmSize(const std::string& size) {
        if (size == "slim")
            return ArmSize::Slim;

        return ArmSize::Wide;
    };
};

#endif //ARMSIZE_HPP
