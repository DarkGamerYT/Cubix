#ifndef ACTORRUNTIMEID_HPP
#define ACTORRUNTIMEID_HPP

#include <cstdint>
#include <random>

#include "../../util/BinaryStream.hpp"

static inline int32_t runtimeIdCounter = 1;
class ActorRuntimeId {
private:
    uint64_t mRawId;

public:
    ActorRuntimeId() : mRawId(runtimeIdCounter++) {};
    explicit ActorRuntimeId(const uint64_t id) : mRawId(id) {};

    uint64_t getValue() const { return this->mRawId; };

    bool operator==(ActorRuntimeId const& o) const { return this->getValue() == o.getValue(); };
};

template<>
struct BinaryStream::serialize<ActorRuntimeId> {
    static ActorRuntimeId read(BinaryStream& stream) {
        return ActorRuntimeId{ stream.readUnsignedVarLong() };
    };

    static void write(const ActorRuntimeId& value, BinaryStream& stream) {
        stream.writeUnsignedVarLong(value.getValue());
    };
};

template<>
struct std::hash<ActorRuntimeId> {
    size_t operator()(ActorRuntimeId const& k) const noexcept {
        return std::hash<uint64_t>()(k.getValue());
    };
};

#endif //ACTORRUNTIMEID_HPP
