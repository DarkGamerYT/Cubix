#ifndef ACTORUNIQUEID_HPP
#define ACTORUNIQUEID_HPP

#include <cstdint>
#include <random>

#include "../../util/UUID.hpp"

class ActorUniqueId {
private:
    int64_t mRawId;

public:
    explicit ActorUniqueId(const int64_t id) : mRawId(id) {};
    ActorUniqueId() {
        static std::mt19937_64 gen(std::random_device{}());
        this->mRawId = static_cast<int64_t>(gen());
    };

    int64_t getValue() const { return this->mRawId; };

    static ActorUniqueId fromUUID(const Util::UUID& uuid) {
        return ActorUniqueId{ static_cast<int64_t>(uuid.getLeastSignificantBits() ^ uuid.getMostSignificantBits()) };
    };

    bool operator==(ActorUniqueId const& o) const { return this->getValue() == o.getValue(); };
};

template<>
struct BinaryStream::serialize<ActorUniqueId> {
    static ActorUniqueId read(BinaryStream& stream) {
        return ActorUniqueId{ stream.readSignedVarLong() };
    };

    static void write(const ActorUniqueId& value, BinaryStream& stream) {
        stream.writeSignedVarLong(value.getValue());
    };
};

template<>
struct std::hash<ActorUniqueId> {
    size_t operator()(ActorUniqueId const& k) const noexcept {
        return std::hash<int64_t>()(k.getValue());
    };
};

#endif //ACTORUNIQUEID_HPP
