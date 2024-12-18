#ifndef VECTOR_GUNS_H
#define VECTOR_GUNS_H

#include <vector>

#include "gun.h"


class VectorGuns: public std::vector<gun_t> {
private:
public:
    VectorGuns();
    ~VectorGuns();
};


#endif  // VECTOR_GUNS_H
