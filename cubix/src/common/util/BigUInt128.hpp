#ifndef BIGUINT128_HPP
#define BIGUINT128_HPP

#include <cstdint>
#include <utility>

#include "BinaryStream.hpp"

class BigUInt128 {
private:
    uint64_t mLow = 0;
    uint64_t mHigh = 0;

public:
    bool testBit(const int i) const;

    void orShifted(const uint8_t value, const int shift) {
        if (shift < 64)
        {
            mLow |= static_cast<uint64_t>(value) << shift;
        }
        else {
            mHigh |= static_cast<uint64_t>(value) << (shift - 64);
        };
    };

    static BigUInt128 readUnsignedBigVarInt(BinaryStream& stream, const int maxBits);

    std::pair<uint64_t, uint64_t> getParts() const {
        return { mLow, mHigh };
    };
};

#endif //BIGUINT128_HPP
