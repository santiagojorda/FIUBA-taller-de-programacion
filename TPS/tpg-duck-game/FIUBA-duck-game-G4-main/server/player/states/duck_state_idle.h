#ifndef DUCK_STATE_IDLE_H
#define DUCK_STATE_IDLE_H

#include "../duck_state.h"

class DuckStateIdle: public DuckState {
public:
    DuckStateIdle(const uint8_t& _player_id);
    ~DuckStateIdle();
};

#endif
