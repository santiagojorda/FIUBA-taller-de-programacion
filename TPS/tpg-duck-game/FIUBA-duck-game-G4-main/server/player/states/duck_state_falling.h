#ifndef DUCK_STATE_FALLING_H
#define DUCK_STATE_FALLING_H

#include "../duck_state.h"

class DuckStateFalling: public DuckState {
public:
    DuckStateFalling(const uint8_t& _player_id);
    void update_state(Player& player, GameLogic& game_logic) override;
    // void execute(GamePhysics& physics) override;
    ~DuckStateFalling();
};

#endif
