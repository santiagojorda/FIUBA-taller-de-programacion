#include "box.h"

#include <iostream>
#include <random>

#include "../weapons/projectile.h"
#include "../game/game_logic.h"
#include "../weapons/gun_factory.h"

#define TICKS_PER_SECOND 30
#define SECONDS_TO_RESPAWN 20

Box::Box(const Coordinate& _coordinate)
: Positionable((uint8_t)BoxesTextureID::DEFAULT, _coordinate),
        state(GroundState::CLOSE)
    {}

void Box::update(){
    if(is_open()){
        tick++;
        if(tick >= TICKS_PER_SECOND * SECONDS_TO_RESPAWN){
            reset();
        }
    }
}

void Box::drop_weapon(GameLogic& game_logic){
    (void)game_logic;
    // std::random_device rd;  
    // std::mt19937 gen(rd()); 
    // std::uniform_int_distribution<> distrib(1, static_cast<int>(WeaponTextureID::MAX) - 1);

    // int random_number = distrib(gen);
    // GunFactory factory;
    // game_logic.handle_drop(factory.create_gun(random_number, get_coordinate()));

}

void Box::handle_collision(std::shared_ptr<Collidable> other, GameLogic& game_logic) {
    other->on_collision_with(std::dynamic_pointer_cast<Box>(shared_from_this()), game_logic);
}

void Box::on_collision_with(std::shared_ptr<Projectile> projectile, GameLogic& game_logic) {
    projectile->on_collision_with(std::dynamic_pointer_cast<Box>(shared_from_this()), game_logic);
    if(!is_open()){
        open(game_logic);
    }
}



void Box::reset() { 
    tick = 0;
    state = GroundState::CLOSE; 
}
bool Box::is_open() { return state == GroundState::OPEN; }
void Box::open(GameLogic& game_logic) { 
    (void)game_logic;
    state = GroundState::OPEN; 
    drop_weapon(game_logic);
}
uint8_t Box::get_state() { return (uint8_t)state; }
