#include "player.h"

#include <iostream>
#include "../../common/state_duck.h"
#include "../weapons/gun.h"
#include "../game/game_logic.h"
#include "../weapons/list_projectiles.h"
#include "../weapons/projectile.h"
#include "../map/ground.h"
#include "../equipment/armor.h"
#include "../attributes/equippable.h"
#define SIZE_PLAYER 32
#define COLLIDER_OFFSET_X 8

const int SPEED = 1;

Player::Player(uint8_t _id): Positionable(_id, _id, Coordinate(10, 10, SIZE_PLAYER, SIZE_PLAYER)), state(id){}

Player::~Player() { Positionable::~Positionable(); }

void Player::update(GameLogic& game_logic) {     
    state.update(*this, game_logic); 
}

void Player::log_action(const std::string& action) {
    std::cout << "Player " << int(id) << " " << action << std::endl;
}

void Player::run_right(GameLogic& game_logic) { state.run_right(*this, game_logic); }
void Player::run_left(GameLogic& game_logic) { state.run_left(*this, game_logic); }
void Player::jump() { state.jump(); }
void Player::fall(GameLogic& game_logic) { 
    (void)game_logic;
    state.fall(); 
}
void Player::crouch() { state.crouch(); }
void Player::slip() { state.slip(); }
// void Player::plane(GameLogic& game_logic) { state.plane(*this, game_logic); }
void Player::idle() { state.idle(); }
void Player::die(GameLogic& game_logic) {
    health = 0;
    drop_gun(game_logic);
    state.die();
}

void Player::reset(){
    this->state.reset();
    this->inventory.reset();
}

void Player::equip(std::shared_ptr<Equippable> item) { inventory.equip(item); }

void Player::update_gun_position(){
    std::shared_ptr<Gun> gun = inventory.get_gun();
    if (!gun) {
        return;
    }
    gun->set_coordinate(this->get_coordinate());
    gun->set_direction(this->get_direction());
}

void Player::drop_gun(GameLogic& game_logic){ 
    update_gun_position();
    inventory.drop_gun(game_logic); 
}
void Player::drop_armor(){ 
    inventory.drop_armor(); 
}
void Player::drop_helmet(){ 
    inventory.drop_helmet(); 
}

void Player::take_damage(GameLogic& game_logic){
    if(inventory.get_armor()){
        drop_armor();
    }
    else if(inventory.get_helmet()){
        drop_helmet();
    }
    else {
        die(game_logic);
    }
}

uint8_t Player::get_id() const { return this->id; }
std::shared_ptr<Gun> Player::get_gun() { return inventory.get_gun(); }
std::shared_ptr<Armor> Player::get_armor() { return inventory.get_armor(); }
std::shared_ptr<Helmet> Player::get_helmet() { return inventory.get_helmet(); }
Inventory& Player::get_inventory() { return inventory; }
Direction Player::get_direction() { return state.get_direction(); }

void Player::adjust_position_to_floor(std::shared_ptr<Positionable> floor) {
    if (floor) {

        int player_bottom = space.get_y_max();
        Rectangle floor_points = floor->get_rectangle();
        int floor_top = floor_points.get_y_min();
        int difference = player_bottom - floor_top;

        if (difference < 1) {
            translate_y(-(difference + 1));
        } else {
            translate_y(-(difference - 1));
        }
    }
}

bool Player::is_dead_animation_finished() const { return state.is_dead_animation_finished(); }

Coordinate Player::get_coordinates_collisionables(){ 
    Coordinate player_coordinate = get_coordinate();
    int new_x = player_coordinate.get_x() + COLLIDER_OFFSET_X;
    int y = player_coordinate.get_y();
    int h = player_coordinate.get_h();
    int new_w = COLLIDER_OFFSET_X * 2;

    return Coordinate(new_x, y, h, new_w);
}

void Player::handle_collision(std::shared_ptr<Collidable> other, GameLogic& game_logic){
    std::cout << "handle_sollision player" << std::endl;
    other->on_collision_with(*this, game_logic);    
};


void Player::on_collision_with(std::shared_ptr<Equippable> item, GameLogic& game_logic) { 
    if(!is_slipping()){
        equip(item);
    }
    (void)game_logic;
}

void Player::translate_x(int pasos) {
    int boost_speed = 1;
    Positionable::translate_x(pasos*boost_speed);
}

void Player::translate_y(int pasos) {
    int boost_speed = 1; // si queremos 
    Positionable::translate_y(pasos*boost_speed);
}

Player& Player::operator=(const Player& _other) {
    this->id = _other.id;
    this->space = _other.space;
    this->idle();
    return *this;
}

void Player::recoil(GameLogic& game_logic) { 
    state.recoil(*this, game_logic);
}
bool Player::is_jumping() { return state.is_jumping(); }
bool Player::is_running() { return state.is_running(); }
bool Player::is_falling() { return state.is_falling(); }
bool Player::is_slipping() { return state.is_slipping(); }
bool Player::is_idle()  { return state.is_idle(); }
bool Player::is_dead() const { return state.is_dead(); }
bool Player::is_alive() { return state.is_alive(); }

DuckStateType Player::get_state() { return state.get_state(); }

uint8_t Player::get_frame() { return state.get_frame(); }
bool Player::has_equipped_this(std::shared_ptr<Equippable> item){
    return inventory.has_equipped_this(item);
}
bool Player::is_touching_floor() { return state.is_touching_floor(); }
void Player::set_touching_floor(const bool& touch_floor) { state.set_touch_floor(touch_floor); }
void Player::touch_floor(){ state.set_touch_floor(true); }
void Player::leave_floor(){ state.set_touch_floor(false); }

void Player::shoot(GameLogic& game_logic, const ModeShoot& mode) {
    if(is_slipping()){
        return;
    }
    std::shared_ptr<Gun> gun = inventory.get_gun();
    if (!gun) {
        return;
    }
    update_gun_position();
    bool is_dropped = false;
    ShootingRecoil recoil_rate = gun->get_recoil();
    switch (mode)  {
        case ModeShoot::TRIGGER:
            gun->trigger(game_logic.get_projectiles(), id);
            break;
        case ModeShoot::TRIGGER_OUT:
            gun->trigger_out(game_logic.get_projectiles(), id, is_dropped);
            break;
        default:
            break;
    }
    if (is_dropped){
        drop_gun(game_logic);
    }
    if ((int)recoil_rate > 0) {  // is there recoil? yes -> it could be a function
        recoil(game_logic);
    }
}
