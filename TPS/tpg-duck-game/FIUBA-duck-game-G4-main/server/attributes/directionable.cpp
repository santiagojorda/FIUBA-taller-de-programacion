#include "directionable.h"

Directionable::Directionable(const Direction& _diretion) : direction(_diretion)  {}

Direction Directionable::get_direction() { return this->direction; }

void Directionable::set_direction(const Direction& new_diretion){
    this->direction = new_diretion;
}

bool Directionable::is_right() {
    return this->direction == Direction::RIGHT;
}

bool Directionable::is_down() {
    return this->direction == Direction::DOWN;
}

bool Directionable::is_left() {
    return this->direction == Direction::LEFT;
}

bool Directionable::is_up() {
    return this->direction == Direction::UP;
}

int  Directionable::get_direction_int() {
    return (this->direction == Direction::RIGHT) ? 1 : -1; //refactor
}

Directionable::~Directionable() {}

