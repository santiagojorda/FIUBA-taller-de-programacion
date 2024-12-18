#ifndef WEAPONS_ID_H
#define WEAPONS_ID_H

#include <cstdint>
enum class WeaponTextureID : uint8_t {
    GRANATE = 1,
    BANANA,
    PEW_PEW_LASER,
    LASER_RIFLE,
    AK_47,
    DUELING_GUN,
    COWBOY_GUN,
    MAGNUM,
    SHOTGUN,
    SNIPER,
    ARMOR,
    HELMET,
    MAX,
    DUMMY = 99
};

#endif  // WEAPONS_ID_H
