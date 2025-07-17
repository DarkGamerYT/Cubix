#ifndef COMMANDORIGIN_HPP
#define COMMANDORIGIN_HPP

#include <string>

#include "CommandPermissionLevel.hpp"
#include "types/CommandOriginType.hpp"

#include "../../world/actor/player/Player.hpp"

class ServerInstance;
class CommandOrigin {
private:
    CommandOriginType m_type;
    std::string m_requestId;
    Util::UUID m_uuid;
    int64_t m_playerId = 0;
    ServerInstance* m_serverInstance;

public:
    virtual ~CommandOrigin() = default;

    CommandOrigin(
        const CommandOriginType type,
        ServerInstance* serverInstance,
        const Util::UUID& uuid,
        const std::string& requestId
    ) : m_type(type), m_requestId(requestId), m_uuid(uuid), m_serverInstance(serverInstance) {};

    CommandOriginType getType() const { return this->m_type; };
    const std::string& getRequestId() const { return this->m_requestId; };
    const Util::UUID& getUUID() const { return this->m_uuid; };

    void setPlayerId(const int64_t playerId) { this->m_playerId = playerId; };
    int64_t getPlayerId() const { return this->m_playerId; };

    ServerInstance* getServerInstance() const { return this->m_serverInstance; };

    virtual void writeNetwork(BinaryStream& stream);
};

class PlayerCommandOrigin : public CommandOrigin {
private:
    std::shared_ptr<Player> m_player;

public:
    PlayerCommandOrigin(
        ServerInstance* serverInstance,
        const std::shared_ptr<Player>& player,
        const std::unique_ptr<CommandOrigin>& origin
    ) : CommandOrigin(CommandOriginType::Player, serverInstance, origin->getUUID(), origin->getRequestId()),
        m_player(player) {};

    const std::shared_ptr<Player>& getPlayer() const { return this->m_player; };
};

#endif //COMMANDORIGIN_HPP
