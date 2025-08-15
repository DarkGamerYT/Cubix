#ifndef COMMANDORIGIN_HPP
#define COMMANDORIGIN_HPP

#include <string>

#include "types/CommandPermissionLevel.hpp"
#include "types/CommandOriginType.hpp"

#include "../../world/actor/player/Player.hpp"

class ServerInstance;
class CommandOrigin {
    friend struct BinaryStream::serialize<CommandOrigin>;

private:
    CommandOriginType mType;
    std::string mRequestId;
    Util::UUID mUUID;
    ActorUniqueId mPlayerId{ -1 };
    ServerInstance* mServerInstance;

public:
    virtual ~CommandOrigin() = default;

    CommandOrigin(
        const CommandOriginType type,
        ServerInstance* serverInstance,
        const Util::UUID& uuid,
        const std::string& requestId,
        const ActorUniqueId& playerId = ActorUniqueId{ -1 }
    ) : mType(type), mRequestId(requestId), mUUID(uuid), mServerInstance(serverInstance), mPlayerId(playerId) {};

    CommandOriginType getType() const { return this->mType; };
    const std::string& getRequestId() const { return this->mRequestId; };
    const Util::UUID& getUUID() const { return this->mUUID; };

    void setPlayerId(const ActorUniqueId& playerId) { this->mPlayerId = playerId; };
    const ActorUniqueId& getPlayerId() const { return this->mPlayerId; };

    ServerInstance* getServerInstance() const { return this->mServerInstance; };
};

class PlayerCommandOrigin final : public CommandOrigin {
private:
    std::shared_ptr<Player> mPlayer;

public:
    PlayerCommandOrigin(
        ServerInstance* serverInstance,
        const std::shared_ptr<Player>& player,
        const std::unique_ptr<CommandOrigin>& origin
    ) : CommandOrigin(CommandOriginType::Player, serverInstance, origin->getUUID(), origin->getRequestId()),
        mPlayer(player) {};

    const std::shared_ptr<Player>& getPlayer() const { return this->mPlayer; };
};

template <>
struct BinaryStream::serializeTraits<CommandOrigin> {
    using readType = std::unique_ptr<CommandOrigin>;
    using writeType = const std::unique_ptr<CommandOrigin>&;
};

template <>
struct BinaryStream::serialize<CommandOrigin> {
    using traits   = BinaryStream::serializeTraits<CommandOrigin>;
    using readType = traits::readType;
    using writeType = traits::writeType;

    static readType read(BinaryStream& stream);
    static void write(writeType value, BinaryStream& stream);
};

#endif //COMMANDORIGIN_HPP
