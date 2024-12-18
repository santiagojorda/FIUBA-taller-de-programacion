#include "duck_state_slipping.h"

#include <iostream>

#include <math.h>

#include "../player.h"

#define SLIP_STEP 4
#define SLIP_TICKS_PER_FRAME 10
#define TILE_SIZE_PLAYER 16
#define MAX_SLIPPING_DISTANCE 100
struct SlippingStateConfig {
    DuckStateType id = DuckStateType::SLIPPING;
    std::string name = "Sliping";
};
SlippingStateConfig slipping_config;

DuckStateSlipping::DuckStateSlipping(const uint8_t& _player_id):
        DuckState(slipping_config.id, slipping_config.name,
                  duck_state_frames[slipping_config.id].max_frames, _player_id) {}

void DuckStateSlipping::update_state(Player& player, GameLogic& game_logic) {
    tick++;
    if (tick % SLIP_TICKS_PER_FRAME == 0) {
        increment_frame();
    }
    int coef = (player.get_direction() == Direction::LEFT) ? -1 : 1;

    game_logic.move(player, coef * SLIP_STEP, 0);

    total_slip_distance += coef * SLIP_STEP;

    if ((has_reached_max_frames() &&
         std::abs(total_slip_distance) >= MAX_SLIPPING_DISTANCE * TILE_SIZE_PLAYER)) {
        player.idle();
        total_slip_distance = 0;
        tick = 0;
        return;
    }

    // game_logic.move(player, 0, -JUMP_STEP);

    // if (has_reached_max_frames()) {
    //     player.fall(game_logic);
    //     return;
    // }
    // if (tick % JUMP_TICKS_PER_FRAME == 0) {
    //     increment_frame();
    // }
}

DuckStateSlipping::~DuckStateSlipping() {}