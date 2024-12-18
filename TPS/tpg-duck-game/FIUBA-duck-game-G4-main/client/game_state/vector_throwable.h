#ifndef VECTOR_THROWABLE_h
#define VECTOR_THROWABLE_h

#include <vector>

#include "sprite.h"

struct throwable_t {
    sprite_t throwable;
    uint8_t frame;
    uint8_t state;
};

class VectorThrowable: public std::vector<throwable_t> {
private:
public:
    VectorThrowable();
    ~VectorThrowable();
};


#endif  // VECTOR_THROWABLE_h
