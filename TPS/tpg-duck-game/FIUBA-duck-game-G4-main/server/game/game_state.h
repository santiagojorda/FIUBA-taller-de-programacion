#ifndef SERVER_GAME_STATE_H_
#define SERVER_GAME_STATE_H_

#include <list>

#include "list_items_map.h"
#include "game_statistics.h"
#include "../weapons/list_projectiles.h"
#include "../map/map.h"
#include "../player/list_players.h"
#include "../player/player.h"

#include "../../common/game_moment.h"

struct ItemsMap_t{
    uint8_t texture_id;
    Coordinate coordinate;
    uint8_t frame;
};

struct Projectiles_t{
    uint8_t texture_id;
    Coordinate coordinate;
    uint8_t direction;

};

struct Box_t{
    uint8_t texture_id;
    Coordinate coordinate;
    uint8_t frame;
};


struct GameState_t {
    GameMoment moment;
    ListPlayers& players;
    Map& map;
    std::list<ItemsMap_t> map_items;
    std::list<Projectiles_t> map_projectiles;
    std::list<Box_t> map_boxes;
    game_statistics_t statistics;
};


#endif  // SERVER_GAME_STATE_H_
