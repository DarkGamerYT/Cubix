#ifndef COMMANDORIGIN_HPP
#define COMMANDORIGIN_HPP

#include <string>

#include "types/CommandPermissionLevel.hpp"
#include "types/CommandOriginType.hpp"

#include "../../world/actor/player/Player.hpp"

class ServerInstance;
class CommandOrigin {
private:
    CommandOriginType mType;
    std::string mRequestId;
    Util::UUID mUuid;
    int64_t mPlayerId = 0;
    ServerInstance* mServerInstance;

public:
    virtual ~CommandOrigin() = default;

    CommandOrigin(
        const CommandOriginType type,
        ServerInstance* serverInstance,
        const Util::UUID& uuid,
        const std::string& requestId
    ) : mType(type), mRequestId(requestId), mUuid(uuid), mServerInstance(serverInstance) {};

    CommandOriginType getType() const { return this->mType; };
    const std::string& getRequestId() const { return this->mRequestId; };
    const Util::UUID& getUUID() const { return this->mUuid; };

    void setPlayerId(const int64_t playerId) { this->mPlayerId = playerId; };
    int64_t getPlayerId() const { return this->mPlayerId; };

    ServerInstance* getServerInstance() const { return this->mServerInstance; };

    virtual void writeNetwork(BinaryStream& stream);
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

#endif //COMMANDORIGIN_HPP
