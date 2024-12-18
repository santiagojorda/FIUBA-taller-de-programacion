#include "duck_state_falling.h"

#include "../../attributes/directionable.h"
#include "../../attributes/positionable.h"
#include "../player.h"

#define FALLING_TICK_PER_FRAME 3

struct FallingStateConfig {
    DuckStateType id = DuckStateType::FALLING;
    std::string name = "Falling";
};
FallingStateConfig falling_config;

DuckStateFalling::DuckStateFalling(const uint8_t& _player_id):
        DuckState(falling_config.id, falling_config.name,
                  duck_state_frames[falling_config.id].max_frames, _player_id) {}

void DuckStateFalling::update_state(Player& player, GameLogic& game_logic) {
    game_logic.fall(player);
    tick++;
    if (tick % FALLING_TICK_PER_FRAME == 0) {
        increment_frame();
    }
}
DuckStateFalling::~DuckStateFalling() {}
