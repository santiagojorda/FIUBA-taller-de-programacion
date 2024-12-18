
#include "duck_state.h"

#include <iostream>
#include "../game/game_logic.h"


DuckState::DuckState(const DuckStateType& _state_id, const std::string& _state_name,
                     const uint8_t& _max_frames, const uint8_t& _player_id):
        State<DuckStateType>(_state_id, _state_name, _max_frames),
        player_id(_player_id)
        {
            init_state(_player_id);
        }


void DuckState::init_state(const uint8_t& player_id) {
    std::cout << "State " << state_name << " of player " << (int)player_id << " is created "
              << std::endl;
    reset();
}

void DuckState::update_state(Player& player, GameLogic& game_logic) {
    (void)game_logic;
    (void)player;
}
void DuckState::execute(Player& player, GameLogic& game_logic) {
    (void)game_logic;
    (void)player;
}

void DuckState::reset() {
    State::reset();
    Updatable::reset();
}

void DuckState::start() {
    std::cout << "Player " << (int)player_id << " is " << state_name << std::endl;
    reset();
}

void DuckState::finish() { reset(); }


DuckState::~DuckState() {}
