#include "duck_state_recoiling.h"

#include "../player.h"
#define RECOIL_STEP 5
#define TICKS_TO_FINISH_STATE 20

struct RecoilingStateConfig {
    DuckStateType id = DuckStateType::RUNNING;
    std::string name = "Recoiling";
};
RecoilingStateConfig recoiling_config;
DuckStateRecoiling::DuckStateRecoiling(const uint8_t& _player_id):
        DuckState(recoiling_config.id, recoiling_config.name,
                  duck_state_frames[recoiling_config.id].max_frames, _player_id) {}

void DuckStateRecoiling::update_state(Player& player, GameLogic& game_logic) {
    (void)game_logic;
    (void)player;
    tick++;
    if (tick % TICKS_TO_FINISH_STATE == 0) {
        player.idle();
    }
    if (has_reached_max_frames()) {
        reset();
    }
}

void DuckStateRecoiling::move(Player& player, GameLogic& game_logic) {
    int sign;
    if (player.get_direction() == Direction::LEFT) {
        sign = 1;
    } else {
        sign = -1;
    }

    game_logic.move(player, sign * RECOIL_STEP, 0);
}

void DuckStateRecoiling::execute(Player& player, GameLogic& game_logic) {
    move(player, game_logic);
    increment_frame();
    tick = 0;
    // player.idle();
}

DuckStateRecoiling::~DuckStateRecoiling() {}
