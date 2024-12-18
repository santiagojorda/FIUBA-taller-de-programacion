#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <cstdint>
#include <vector>

struct game_data_t {
    uint8_t count_players;
    std::vector<uint8_t> id_players;
};

#endif  // GAME_DATA_H