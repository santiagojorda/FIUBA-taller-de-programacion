#ifndef VECTOR_PLAYER_H
#define VECTOR_PLAYER_H

#include <vector>

#include "player.h"
#include "sprite.h"

class VectorPlayers: public std::vector<player_t> {
private:
public:
    VectorPlayers();
    ~VectorPlayers();
};

#endif  // VECTOR_PLAYER_H
