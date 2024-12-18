#include "duck_state_controller.h"

#include <iostream>
#include "../game/game_logic.h"

DuckStateController::DuckStateController(const uint8_t& _player_id)
        : StateController(std::make_shared<DuckStateFactory>(_player_id)),
            touch_floor(true)
        {
            set_state(DuckStateType::IDLE);
            direction = Direction::RIGHT;
            // direction = current_state->get_direction();
        }

void DuckStateController::reset(){
    set_state(DuckStateType::IDLE);
}

void DuckStateController::update(Player& player, GameLogic& game_logic) {
    current_state->update_state(player, game_logic);
}


void DuckStateController::set_direction(const Direction& new_direction) {
    direction = new_direction;
}

void DuckStateController::set_alive_state(const DuckStateType new_state_type){
    if(is_alive()){
        set_state(new_state_type);
        set_direction(direction);
    }
}

void DuckStateController::execute(Player& player, GameLogic& game_logic) {
    current_state->execute(player, game_logic);
}


void DuckStateController::run(Direction new_direction, Player& player, GameLogic& game_logic) {
    if(!is_alive() || is_crouching() || is_slipping() || is_recoiling() || is_planning()){
        return;
    }

    if(is_falling() || is_jumping()){ 
        set_direction(new_direction);
        game_logic.move_horizontal(player, new_direction);
        return;
    }

    if (!is_running()) {
        set_state(DuckStateType::RUNNING);
    }

    set_direction(new_direction);
    execute(player, game_logic);
    
}

void DuckStateController::run_right(Player& player, GameLogic& game_logic) {
    run(Direction::RIGHT, player, game_logic);
}
void DuckStateController::run_left(Player& player, GameLogic& game_logic) {
    run(Direction::LEFT, player, game_logic);
}

void DuckStateController::jump() {
    if(is_touching_floor() && !is_slipping() && !is_slipping()){
        set_touch_floor(false);
        set_alive_state(DuckStateType::JUMPING);
    }
}
void DuckStateController::fall() {
    if(!is_planning()){
        set_touch_floor(false);
        set_alive_state(DuckStateType::FALLING);
    }
}

void DuckStateController::crouch() {
    if(is_touching_floor() && !is_slipping()){
        set_alive_state(DuckStateType::CROUCHING);
    }
    else{
        set_alive_state(DuckStateType::PLANNING);
    }
}
void DuckStateController::slip() {
    set_alive_state(DuckStateType::SLIPPING);
}
void DuckStateController::recoil(Player& player, GameLogic& game_logic) {
    if(!is_alive() || is_crouching() || is_slipping() || is_recoiling()){
        return;
    }

    std::shared_ptr<State<DuckStateType>> prev_state = current_state; 
    set_alive_state(DuckStateType::RECOILING);
    execute(player, game_logic);
    if(is_falling() || is_jumping() || is_planning()){ 
        current_state = prev_state;
    }
}
void DuckStateController::plane(Player& player, GameLogic& game_logic) {
    if(is_alive() && !is_touching_floor()){
        set_state(DuckStateType::PLANNING);
        execute(player, game_logic);
    }
}
void DuckStateController::die() {
    if (!is_dead()) {
        set_alive_state(DuckStateType::DEAD);
    }
}
void DuckStateController::idle() {
    set_alive_state(DuckStateType::IDLE);
    
}

bool DuckStateController::is_jumping() { return is_in_state(DuckStateType::JUMPING); }
bool DuckStateController::is_running() { return is_in_state(DuckStateType::RUNNING); }
bool DuckStateController::is_falling() { return is_in_state(DuckStateType::FALLING); }
bool DuckStateController::is_slipping() { return is_in_state(DuckStateType::SLIPPING); }
bool DuckStateController::is_planning() { return is_in_state(DuckStateType::PLANNING); }
bool DuckStateController::is_recoiling() { return is_in_state(DuckStateType::RECOILING); }
bool DuckStateController::is_crouching() const { return is_in_state(DuckStateType::CROUCHING); }
bool DuckStateController::is_dead() const { return is_in_state(DuckStateType::DEAD); }
bool DuckStateController::is_idle() { return is_in_state(DuckStateType::IDLE); }
bool DuckStateController::is_alive() { return !is_in_state(DuckStateType::DEAD); }
bool DuckStateController::is_touching_floor() { return touch_floor; }
bool DuckStateController::is_dead_animation_finished() const { return is_dead() && current_state->has_reached_max_frames(); }
void DuckStateController::set_touch_floor(const bool& _touch_floor) { touch_floor = _touch_floor; }
DuckStateType DuckStateController::get_state() { return current_state->get_id(); };
uint8_t DuckStateController::get_frame() const { return current_state->get_frame(); };
Direction DuckStateController::get_direction() { return direction; }
DuckStateController::~DuckStateController() {}
