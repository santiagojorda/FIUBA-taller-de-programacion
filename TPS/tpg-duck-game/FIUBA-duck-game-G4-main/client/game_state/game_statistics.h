#ifndef GAME_STATISTICS_H
#define GAME_STATISTICS_H

#include <cstdint>


struct game_statistics_t {
    uint8_t rounds = 0;
    uint8_t id_winer = 0xFF;
};


#endif  // GAME_STATISTICS_H