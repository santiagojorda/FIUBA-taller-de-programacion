#ifndef VECTOR_SPRITE_H
#define VECTOR_SPRITE_H

#include <vector>

#include "sprite.h"

class VectorSprite: public std::vector<sprite_t> {
private:
public:
    VectorSprite();
    ~VectorSprite();
};


#endif  // VECTOR_SPRITE_H
