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
#include "ServerLevel.hpp"
#include "commands/CommandOutput.hpp"

class ServerInstance
{
public:
    enum class InstanceState {
        Running    = 0,
        Stopped    = 1,
        NotStarted = 2
    };

    std::shared_ptr<ServerNetworkHandler> mNetwork;

private:
    int mTicksPerSecond = 20;
    uint32_t mCurrentTick = 0;
    PlayerTickPolicy mPlayerTickPolicy = PlayerTickPolicy::THROTTLED;
    std::atomic<InstanceState> mInstanceState = InstanceState::NotStarted;
    std::thread mServerThread;
    std::shared_ptr<ServerLevel> mLevel;

public:
    ServerInstance();
    ~ServerInstance();

    void initializeServer(
        const LevelSettings&,
        PlayerTickPolicy,
        const ConnectionDefinition&,
        bool requireOnlineAuthentication,
        TransportLayer transportLayer);
    void initializeCommands();
    void startServerThread();
    void shutdown();

    int getCurrentTick() const { return this->mCurrentTick; };
    InstanceState getInstanceState() const { return this->mInstanceState.load(); };
    void waitUntil(const InstanceState desired) const {
        InstanceState current = this->mInstanceState.load();
        while (current != desired) {
            this->mInstanceState.wait(current);
            current = this->mInstanceState.load();
        };
    };

    void onTick(uint32_t) const;
    void runCommand(const std::string& command, const CommandOrigin&, CommandOutput&);
};

#endif // !SERVERINSTANCE_HPP
