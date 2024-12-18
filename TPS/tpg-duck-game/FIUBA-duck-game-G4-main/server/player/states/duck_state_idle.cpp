#include "duck_state_idle.h"

struct IdleStateConfig {
    DuckStateType id = DuckStateType::IDLE;
    std::string name = "Idle";
};
IdleStateConfig idle_config;

DuckStateIdle::DuckStateIdle(const uint8_t& _player_id):
        DuckState(idle_config.id, idle_config.name, duck_state_frames[idle_config.id].max_frames,
                  _player_id) {}

DuckStateIdle::~DuckStateIdle() {}
