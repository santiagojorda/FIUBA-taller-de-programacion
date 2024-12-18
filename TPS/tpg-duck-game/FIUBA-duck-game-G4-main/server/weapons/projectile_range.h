#ifndef PROJECTILE_RANGE
#define PROJECTILE_RANGE

#include <cstdint>

enum class ProjectileRange : uint8_t {
    NONE = 0,
    VERY_SHORT = 5,
    SHORT = 7,
    SHORT_PLUS = 9,
    MEDIUM = 13,
    LARGE = 20,
    VERY_LARGE = 30,
    EXTREME = 35,
    HUGE = 38,
    MAX = 64
};

#endif