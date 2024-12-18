#ifndef ROUND_MANAGER
#define ROUND_MANAGER

#include "game_state.h"
#include  "game_statistics.h"

#include <iostream> 


class RoundManager{
private:
    game_statistics_t statistics;

public:
    explicit RoundManager(const ListPlayers& players);

    bool check_winer(const ListPlayers& players);

    void log_state(std::ostream& log,  const GameState_t& state);

    int get_rounds() const;

    int get_rounds_winer() ;

    uint8_t id_winer() const;

    game_statistics_t get_statistics() const;

    ~RoundManager();
};



#endif // ROUND_MANAGER
