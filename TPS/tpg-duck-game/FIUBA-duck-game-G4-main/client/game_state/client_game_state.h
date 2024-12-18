#ifndef CLIENT_GAME_STATE_H
#define CLIENT_GAME_STATE_H

#include "../../common/game_moment.h"

#include "elements.h"
#include "game_statistics.h"
#include "vector_floor_sprite.h"
#include "vector_guns.h"
#include "vector_player.h"
#include "vector_sprite.h"

struct client_game_state_t {
    GameMoment moment;
    VectorPlayers players;
    std::vector<bullet_t> bullets;
    std::vector<box_t> boxs;
    VectorFloorSprite floors;
    VectorGuns weapons;
    game_statistics_t statistics;
};

#endif  // CLIENT_GAME_STATE_H
