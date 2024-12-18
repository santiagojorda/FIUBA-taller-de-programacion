#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H

#include <memory>
#include "../../common/coordinate.h"
#include "../attributes/positionable.h"
class Map;
class Player;
class ListBoxes;
// #include "../player/player.h"

#define GAME_WIDTH 800
#define GAME_HEIGHT 500
#define IS_TOUCHING_FLOOR true
const int G_FORCE = 10;

class GamePhysics {
private:
    Map& map;
    ListBoxes& boxes;

public:
    GamePhysics(Map& _map, ListBoxes& _boxes);
    bool is_player_out_of_map(Player& player);
    std::shared_ptr<Positionable> get_target_floor_collision(Positionable& target);

    bool exist_collision(const Rectangle& a, const Rectangle& b);

    void falling(Positionable& target, uint iter_frame);
    bool is_this_point_ocuppied(const Coordinate& coordinate);
    std::shared_ptr<Box> get_target_box_collision(Positionable& target);

    ~GamePhysics();
};


#endif  // GAME_PHYSICS_H