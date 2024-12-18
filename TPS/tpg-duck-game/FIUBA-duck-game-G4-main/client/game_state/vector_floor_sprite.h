#ifndef VECTOR_FLOOR_SPRITE_H
#define VECTOR_FLOOR_SPRITE_H

#include <vector>

#include "sprite.h"

class VectorFloorSprite: public std::vector<floor_sprite_t> {
private:
public:
    VectorFloorSprite() {}
    ~VectorFloorSprite() {}
};


#endif  // VECTOR_SPRITE_H
