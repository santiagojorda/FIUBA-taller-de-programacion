#ifndef DUCK_STATE_PLANNING_H
#define DUCK_STATE_PLANNING_H

#include "../duck_state.h"

class DuckStatePlanning: public DuckState {
public:
    DuckStatePlanning(const uint8_t& _player_id);
    void update_state(Player& player, GameLogic& game_logic) override;
    void execute(Player& player, GameLogic& game_logic) override;
    ~DuckStatePlanning();
};

#endif
