#ifndef ELEMENTS_H
#define ELEMENTS_H

#include "sprite.h"

struct bullet_t {
    sprite_t bullet;
    uint8_t frame;
    uint8_t direction;
};

struct box_t {
    sprite_t box;
    uint8_t frame;
};

#endif  // ELEMENTS_H
