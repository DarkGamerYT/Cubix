#ifndef SERVERINSTANCE_HPP
#define SERVERINSTANCE_HPP

#include <thread>
#include <future>
#include <chrono>

#include "../registry/BlockStateRegistry.hpp"
#include "../registry/BlockRegistry.hpp"
#include "../registry/ItemRegistry.hpp"
#include "../registry/CommandRegistry.hpp"

#include "../util/Logger.hpp"

#include "../network/ConnectionDefinition.hpp"
#include "../network/ServerNetworkHandler.hpp"

#include "PlayerTickPolicy.hpp"
#include "commands/CommandOutput.hpp"

class ServerInstance
{
public:
    enum class InstanceState {
        Running    = 0,
        Stopped    = 1,
        NotStarted = 2
    };

    std::shared_ptr<ServerNetworkHandler> m_Network;

private:
    int m_TicksPerSecond = 20;
    uint32_t m_CurrentTick = 0;
    PlayerTickPolicy m_PlayerTickPolicy = PlayerTickPolicy::THROTTLED;
    std::atomic<InstanceState> m_InstanceState = InstanceState::NotStarted;
    std::thread m_ServerThread;

public:
    ServerInstance();
    ~ServerInstance();

    void initializeServer(PlayerTickPolicy, const ConnectionDefinition&);
    void initializeCommands();
    void startServerThread();
    void shutdown();

    int getCurrentTick() const { return this->m_CurrentTick; };
    InstanceState getInstanceState() const { return this->m_InstanceState.load(); };
    void waitUntil(const InstanceState desired) const {
        InstanceState current = this->m_InstanceState.load();
        while (current != desired) {
            this->m_InstanceState.wait(current);
            current = this->m_InstanceState.load();
        };
    };

    void onTick(uint32_t) const;
    void runCommand(const std::string& command, const CommandOrigin&, CommandOutput&);
};

#endif // !SERVERINSTANCE_HPP
