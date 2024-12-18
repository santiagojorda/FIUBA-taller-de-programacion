#include "duck_state_crouching.h"

struct CrouchingStateConfig {
    DuckStateType id = DuckStateType::CROUCHING;
    std::string name = "Crouching";
};
CrouchingStateConfig crouching_config;

DuckStateCrouching::DuckStateCrouching(const uint8_t& _player_id):
        DuckState(crouching_config.id, crouching_config.name,
                  duck_state_frames[crouching_config.id].max_frames, _player_id) {}

DuckStateCrouching::~DuckStateCrouching() {}
