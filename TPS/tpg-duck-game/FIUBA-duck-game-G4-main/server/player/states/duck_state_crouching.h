#ifndef DUCK_STATE_CROUCHING_H
#define DUCK_STATE_CROUCHING_H

#include "../duck_state.h"

class DuckStateCrouching: public DuckState {
public:
    DuckStateCrouching(const uint8_t& _player_id);
    ~DuckStateCrouching();
};

#endif
