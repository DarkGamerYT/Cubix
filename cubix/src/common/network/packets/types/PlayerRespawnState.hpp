#ifndef PLAYERRESPAWNSTATE_HPP
#define PLAYERRESPAWNSTATE_HPP

enum class PlayerRespawnState : uint8_t {
    SearchingForSpawn  = 0x00,
    ReadyToSpawn       = 0x01,
    ClientReadyToSpawn = 0x02
};

#endif //PLAYERRESPAWNSTATE_HPP
