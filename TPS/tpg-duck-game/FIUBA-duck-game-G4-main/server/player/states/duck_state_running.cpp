#include "duck_state_running.h"

#include <iostream>

#include "../../../common/direction.h"
#include "../player.h"

#define RUN_STEP 5

struct RunningStateConfig {
    DuckStateType id = DuckStateType::RUNNING;
    std::string name = "Running";
};
RunningStateConfig running_config;

DuckStateRunning::DuckStateRunning(const uint8_t& _player_id):
        DuckState(running_config.id, running_config.name,
                  duck_state_frames[running_config.id].max_frames, _player_id) {}

void DuckStateRunning::update_state(Player& player, GameLogic& game_logic) {
    (void)game_logic;
    (void)player;
    if (has_reached_max_frames()) {
        reset();
    }
}

void DuckStateRunning::move(Player& player, GameLogic& game_logic) {
    int sign;
    if (player.get_direction() == Direction::RIGHT) {
        sign = 1;
    } else if (player.get_direction() == Direction::LEFT) {
        sign = -1;
    }

    game_logic.move(player, sign * RUN_STEP, 0);
}

void DuckStateRunning::execute(Player& player, GameLogic& game_logic) {
    move(player, game_logic);
    increment_frame();
}

DuckStateRunning::~DuckStateRunning() {}
