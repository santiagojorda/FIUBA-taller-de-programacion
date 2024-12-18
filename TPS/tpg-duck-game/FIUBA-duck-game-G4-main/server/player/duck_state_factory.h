#ifndef DUCK_STATE_FACTORY_h
#define DUCK_STATE_FACTORY_h

#include <cstdint>
#include <memory>

#include "../../common/state_duck.h"

#include "duck_state.h"
#include "states/duck_state_crouching.h"
#include "states/duck_state_dead.h"
#include "states/duck_state_falling.h"
#include "states/duck_state_idle.h"
#include "states/duck_state_jumping.h"
#include "states/duck_state_planning.h"
#include "states/duck_state_recoiling.h"
#include "states/duck_state_running.h"
#include "states/duck_state_slipping.h"

#include "../utils/state_factory.h"

class DuckStateFactory : public StateFactory<DuckStateType> {
private:
    // cppcheck-suppress unusedStructMember
    uint8_t player_id;

public:
    explicit DuckStateFactory(const uint8_t& _player_id): player_id(_player_id) {
        add(DuckStateType::RUNNING,         std::make_shared<DuckStateRunning>(player_id));
        add(DuckStateType::JUMPING,         std::make_shared<DuckStateJumping>(player_id));
        add(DuckStateType::FALLING,         std::make_shared<DuckStateFalling>(player_id));
        add(DuckStateType::CROUCHING,       std::make_shared<DuckStateCrouching>(player_id));
        add(DuckStateType::SLIPPING,        std::make_shared<DuckStateSlipping>(player_id));
        add(DuckStateType::RECOILING,       std::make_shared<DuckStateRecoiling>(player_id));
        add(DuckStateType::PLANNING,        std::make_shared<DuckStatePlanning>(player_id));
        add(DuckStateType::DEAD,            std::make_shared<DuckStateDead>(player_id));
        add(DuckStateType::IDLE,            std::make_shared<DuckStateIdle>(player_id));
    }

    
};

#endif  // EVENT_FACTORY_h
