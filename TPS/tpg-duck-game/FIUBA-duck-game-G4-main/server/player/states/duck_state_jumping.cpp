#include "duck_state_jumping.h"

#include <iostream>

#include "../player.h"

#define JUMP_STEP 8
#define JUMP_TICKS_PER_FRAME 3

struct JumpingStateConfig {
    DuckStateType id = DuckStateType::JUMPING;
    std::string name = "Jumping";
};
JumpingStateConfig jumping_config;

DuckStateJumping::DuckStateJumping(const uint8_t& _player_id):
        DuckState(jumping_config.id, jumping_config.name,
                  duck_state_frames[jumping_config.id].max_frames, _player_id) {}

void DuckStateJumping::update_state(Player& player, GameLogic& game_logic) {
    tick++;

    game_logic.move(player, 0, -JUMP_STEP);

    if (has_reached_max_frames()) {
        player.fall(game_logic);
        return;
    }
    if (tick % JUMP_TICKS_PER_FRAME == 0) {
        increment_frame();
    }
}

DuckStateJumping::~DuckStateJumping() {}
