#ifndef DUCK_STATE_RUNNING_H
#define DUCK_STATE_RUNNING_H

#include "../duck_state.h"

class DuckStateRunning: public DuckState {
private:
public:
    explicit DuckStateRunning(const uint8_t& _player_id);

    void update_state(Player& player, GameLogic& game_logic) override;
    void execute(Player& player, GameLogic& game_logic) override;
    void move(Player& player, GameLogic& game_logic);

    ~DuckStateRunning();
};

#endif
