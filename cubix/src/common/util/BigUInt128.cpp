#include "BigUInt128.hpp"
bool BigUInt128::testBit(const int i) const {
    if (i < 0 || i >= 128)
        return false;

    return (i < 64) ? ((this->mLow >> i) & 1) : ((this->mHigh >> (i - 64)) & 1);
};

BigUInt128 BigUInt128::readUnsignedBigVarInt(BinaryStream& stream, const int maxBits) {
    BigUInt128 result;
    int shift = 0;

    while (true)
    {
        if (shift >= maxBits)
            throw std::runtime_error("Malformed VarInt: too many bytes");

        const uint8_t byte = stream.readByte();
        result.orShifted(byte & 0x7F, shift);

        if ((byte & 0x80) == 0)
            return result;

        shift += 7;
    };
};