#ifndef STATE_DUCK_COMMON_H
#define STATE_DUCK_COMMON_H

#include <cstdint>
#include <unordered_map>

enum class DuckStateType : uint8_t {
    JUMPING,
    RUNNING,
    CROUCHING,
    RECOILING,
    FALLING,
    SLIPPING,
    PLANNING,
    IDLE,
    DEAD,
    AERO_RUNNING
};

struct DuckStateInfo_t {
    uint8_t max_frames;
};

// Mapa que asocia el estado con su información de frames
extern std::unordered_map<DuckStateType, DuckStateInfo_t> duck_state_frames;

#endif
