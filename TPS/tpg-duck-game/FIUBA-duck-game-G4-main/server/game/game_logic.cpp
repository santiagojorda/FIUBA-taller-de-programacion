#include "game_logic.h"

#include <iostream>

#include "list_items_map.h"
#include "../events/event.h"
#include "../../common/state_duck.h"
#include "../player/list_players.h"
#include "../weapons/list_projectiles.h"
#include "list_boxes.h"
#include "../map/ground.h"
#include "../weapons/projectile.h"
#include "../weapons/projectiles/bullet.h"
#include "../weapons/gun.h"

#define DROP_DISTANCE 40
#define HORIZONTAL_STEP 5

GameLogic::GameLogic(ListPlayers& _players, Map& _map, ListItemsMap& _items,
                     ListProjectiles& _projectiles, ListBoxes& _boxes):
        players(_players),
        map(_map),
        items(_items),
        projectiles(_projectiles),
        boxes(_boxes),
        physics(map, boxes) {}

void GameLogic::update_player_equip_collision(Player& player) {
    for (std::shared_ptr<Equippable> item: items) {
        if (this->physics.exist_collision(player.get_rectangle(), item->get_rectangle())) {
            
            player.handle_collision(item, *this);
            if(player.has_equipped_this(item)){
                items.remove_item(item);
                return;
            }

        }
    }
}

void GameLogic::handle_drop(std::shared_ptr<Equippable> item){
    items.push_back(item);
    item->translate_x(DROP_DISTANCE);
}

void GameLogic::update_player_gravity(Player& player) {
    std::shared_ptr<Positionable> touched_floor = physics.get_target_floor_collision(player);
    if (touched_floor) {
        player.adjust_position_to_floor(touched_floor);
        if (player.is_falling()) {
            player.idle();
        }
        player.touch_floor();
    } else {
        player.fall(*this);
    }

}


void GameLogic::update_projectiles(){

    projectiles.erase(
        std::remove_if(projectiles.begin(), projectiles.end(),
                       [](const std::shared_ptr<Projectile>& projectile) {
                           return projectile->is_dead(); 
                       }),
        projectiles.end());
    
    for (std::shared_ptr<Projectile> projectile: projectiles){
        std::shared_ptr<Ground> touched_floor = std::dynamic_pointer_cast<Ground>(physics.get_target_floor_collision(*projectile));
        std::shared_ptr<Box> touched_box = physics.get_target_box_collision(*projectile);
        if(touched_floor){
            projectile->handle_collision(touched_floor, *this);
        }
        else if (touched_box){
            projectile->handle_collision(touched_box, (*this));
        }
        projectile->update(*this);
    }

}


void GameLogic::move(std::shared_ptr<Projectile> projectile, int x, int y){

    for(Player& player : players){
        if(player.is_dead() || player.get_id() == projectile->get_shooter_id()){
            continue;
        }

        if (physics.exist_collision(player.get_rectangle(), projectile->get_rectangle())){
            player.handle_collision(projectile, *this);
            return;
        }
    }
    
    projectile->translate_x(x);
    projectile->translate_y(y);
}


void GameLogic::fall(Player& player){
    physics.falling(player, 1);
}

void GameLogic::move_horizontal(Player& player, Direction& direction){
    int sign = 0;

    if (direction == Direction::RIGHT) {
        sign = 1; 
    } else if (direction == Direction::LEFT) {
        sign = -1;
    }
    
    move(player, sign*HORIZONTAL_STEP, 0);
}

bool GameLogic::can_move(Player& player, int x, int y){
    Coordinate point = Coordinate(
        player.get_coordinate().get_x() + x,
        player.get_coordinate().get_y() + y,
        0, 
        0);
    if(physics.is_this_point_ocuppied(point)){
        return false;
    }
    return true;
}

void GameLogic::move(Player& player, int x, int y){

    if(can_move(player, x, y)){
        player.translate_x(x);
        player.translate_y(y);
    }
    
}

// void GameLogic::apply_weapons_gravity(){

// }

void GameLogic::update_weapons(){
    items.erase(
        std::remove_if(items.begin(), items.end(),
                       [](const std::shared_ptr<Equippable>& item) {
                           return item->is_dead(); 
                       }),
        items.end());

    for (std::shared_ptr<Equippable> item: items) {
        // apply_weapons_gravity();
        item->update(*this);
    }
}

void GameLogic::update(){

    update_projectiles();
    update_players();
    update_weapons();
    update_boxes();
}

void GameLogic::update_boxes(){

    for (std::shared_ptr<Box> box: boxes) {
        box->update();
    }
}

void GameLogic::add_projectile(std::shared_ptr<Projectile> new_projectile){
    projectiles.push_back(new_projectile);
}

void GameLogic::explote(Gun& gun){ 
    gun.handle_explotion(*this); 
}

void GameLogic::update_players() {
    for (Player& player: players) {

        if (player.is_dead()) {
            player.update(*this);
            continue;
        }


        if (physics.is_player_out_of_map(player)) {
            player.die(*this);
            continue;
        }

        else {
            player.update(*this);
            if (!player.is_jumping()) {
                update_player_gravity(player);
            }
            update_player_equip_collision(player);
        }
    }
}


Player& GameLogic::get_player(const uint8_t& _player_id) {
    for (Player& player: players) {
        if (player.get_id() == _player_id) {
            return player;
        }
    }
    throw std::runtime_error("Player con ID no encontrado");
}

void GameLogic::handle_event(Event& event) { event.execute(*this);}

ListProjectiles& GameLogic::get_projectiles() { return projectiles;}
GamePhysics& GameLogic::get_physics() { return physics;}


GameLogic::~GameLogic() {}
