#ifndef GAME_STATISTICS_H
#define GAME_STATISTICS_H

#include <cstdint>
#include <map>


struct game_statistics_t {
    uint8_t id_winer = 0xFF;
    std::map<uint8_t,int> count_winer;
    int rounds = 0 ;
};









#endif // GAME_STATISTICS_H
