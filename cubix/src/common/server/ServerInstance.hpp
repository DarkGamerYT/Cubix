#ifndef SERVERINSTANCE_HPP
#define SERVERINSTANCE_HPP

#include <thread>
#include <chrono>

#include "../registry/BlockStateRegistry.hpp"
#include "../registry/BlockRegistry.hpp"
#include "../registry/ItemRegistry.hpp"
#include "../registry/CommandRegistry.hpp"

#include "../util/Logger.hpp"

#include "../network/ConnectionDefinition.hpp"
#include "../network/ServerNetworkHandler.hpp"

#include "PlayerTickPolicy.hpp"

class ServerInstance
{
public:
    enum class InstanceState : int {
        Running    = 0,
        Stopped    = 1,
        NotStarted = 2
    };

    std::shared_ptr<ServerNetworkHandler> m_Network;

private:
    int m_TicksPerSecond = 20;
    int m_CurrentTick = 0;
    PlayerTickPolicy m_PlayerTickPolicy = PlayerTickPolicy::GREEDY;
    std::atomic<InstanceState> m_InstanceState = InstanceState::NotStarted;

public:
    ServerInstance();
    ~ServerInstance();

    void initializeServer(PlayerTickPolicy, const ConnectionDefinition&);
    void initializeCommands();
    void startServerThread();
    void shutdown();

    InstanceState getInstanceState() const { return this->m_InstanceState; };
    int getCurrentTick() const { return this->m_CurrentTick; };

    void onTick(int) const;
    void runCommand(const std::string& command, const CommandOrigin&/*, CommandOutput&*/);
};

#endif // !SERVERINSTANCE_HPP
