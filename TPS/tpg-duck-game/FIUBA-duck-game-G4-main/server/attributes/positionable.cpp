#include "positionable.h"

#include "../player/player.h"
#include "../weapons/projectiles/bullet.h"

Positionable::Positionable(): space(0, 0, 0, 0) {}  // DUMMY

Positionable::Positionable(const uint8_t& _texture_id) : texture_id(_texture_id), space(0,0,0,0){}
Positionable::Positionable(const uint8_t& _texture_id, const Coordinate& _coordinate):
        texture_id(_texture_id), space(_coordinate) {}

Positionable::Positionable(const uint8_t& _id, const uint8_t& _texture_id,
                           const Coordinate& _coordinate):
        texture_id(_texture_id), id(_id), space(_coordinate) {}

Coordinate Positionable::get_coordinate() const { return this->space.get_coordinates(); }

void Positionable::set_coordinate(const Coordinate& new_coordinate) {
    this->space.operator=(Rectangle(new_coordinate));
}

void Positionable::translate() {}
void Positionable::translate_x(int steps) {
    Rectangle new_pos(this->space.get_coordinates() + Coordinate(steps, 0, 0, 0));
    this->space = new_pos;
}

void Positionable::translate_y(int steps) {
    Rectangle new_pos(this->space.get_coordinates() + Coordinate(0, steps, 0, 0));
    this->space = new_pos;
}

void Positionable::fall(GameLogic& game_logic) { (void)game_logic;}

Rectangle Positionable::get_rectangle() const { return this->space; }

uint8_t Positionable::get_id() const { return id; }
uint8_t Positionable::get_texture_id()  const { return texture_id; }

Positionable::~Positionable() {}