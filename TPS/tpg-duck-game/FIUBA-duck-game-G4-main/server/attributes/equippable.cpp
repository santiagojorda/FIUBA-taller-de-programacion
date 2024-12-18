#include "equippable.h"

#include "../player/player.h"

Equippable::Equippable() {}

Equippable::Equippable(const uint8_t _texture_id) : Positionable(_texture_id) {}

Equippable::Equippable(const uint8_t& _texture_id, const Coordinate& _coordinate) 
    : Positionable(_texture_id, _coordinate), state(EquippableState::ALIVE), frame(0) {}

void Equippable::on_collision_with(Player& player, GameLogic& game_logic) {
    player.on_collision_with(std::dynamic_pointer_cast<Equippable>(shared_from_this()), game_logic);    
};
void Equippable::on_collision_with(std::shared_ptr<Projectile> projectile, GameLogic& game_logic) {
    projectile->on_collision_with(std::dynamic_pointer_cast<Equippable>(shared_from_this()), game_logic);    
};

void Equippable::handle_collision(std::shared_ptr<Collidable> other, GameLogic& game_logic) {
    other->on_collision_with(std::dynamic_pointer_cast<Equippable>(shared_from_this()), game_logic);    
};
void Equippable::update(GameLogic& game_logic) {
    (void)game_logic; // Método virtual puro en subclases, implementación base vacía.
}

void Equippable::die() {
    state = EquippableState::DEAD;
}

bool Equippable::is_dead() {
    return state == EquippableState::DEAD;
}

uint8_t Equippable::send_frame() {
    return frame;
}