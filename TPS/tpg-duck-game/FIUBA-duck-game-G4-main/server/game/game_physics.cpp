#include "game_physics.h"

#include <iostream>
#include "../player/player.h"
#include "../map/map.h"
#include "list_boxes.h"
#include "../map/ground.h"
#define PHYSIC_TILE_SIZE 16

GamePhysics::GamePhysics(Map& _map, ListBoxes& _boxes): map(_map), boxes(_boxes) {}

bool GamePhysics::exist_collision(const Rectangle& a, const Rectangle& b) {
    return !(a.get_x_max() < (b.get_x_min()) || a.get_x_min() > b.get_x_max() ||
             a.get_y_max() < (b.get_y_min()) || a.get_y_min() > b.get_y_max());
}

bool GamePhysics::is_this_point_ocuppied(const Coordinate& coordinate){
    for (auto& tile: this->map) {
        if (this->exist_collision(Rectangle(coordinate), tile->get_rectangle())) {
            return true;
        }
    }

    return false;
}

void GamePhysics::falling(Positionable& target, uint iter_frame) {
    target.translate_y(iter_frame * iter_frame * (G_FORCE / 2));
}

std::shared_ptr<Positionable> GamePhysics::get_target_floor_collision(Positionable& target) {
    for (auto& tile: this->map) {
        if (this->exist_collision(target.get_rectangle(), tile->get_rectangle())) {
            return std::shared_ptr<Positionable>(tile);
        }
    }
    return nullptr;
}


std::shared_ptr<Box> GamePhysics::get_target_box_collision(Positionable& target) {
    for (auto& box: this->boxes) {
        if (this->exist_collision(target.get_rectangle(), box->get_rectangle())) {
            return box;
        }
    }
    return nullptr;
}

bool GamePhysics::is_player_out_of_map(Player& player) {
    Rectangle player_space = player.get_rectangle();
    if (player_space.get_x_max() < 0 || player_space.get_y_max() < 0 ||
        player_space.get_x_min() > GAME_WIDTH || player_space.get_y_min() > GAME_HEIGHT) {
        return true;
    }
    return false;
}


GamePhysics::~GamePhysics() {}
