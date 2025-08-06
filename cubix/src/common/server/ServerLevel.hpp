#ifndef SERVERLEVEL_HPP
#define SERVERLEVEL_HPP

#include "../world/level/Level.hpp"

class ServerInstance;
class ServerLevel : public Level {
private:
    ServerInstance* mServerInstance;

public:
    explicit ServerLevel(ServerInstance* instance)
        : mServerInstance(instance) {};

    void tick(uint32_t tick);
};

#endif //SERVERLEVEL_HPP
