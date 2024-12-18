#include "ground.h"
#include "../weapons/projectile.h"  

Ground::Ground(const Coordinate& _coordinate, const uint8_t& _texture_id) 
        : Positionable(_texture_id, _coordinate), state(0) {}


void Ground::handle_collision(std::shared_ptr<Collidable> other, GameLogic& game_logic) {
    other->on_collision_with(std::dynamic_pointer_cast<Ground>(shared_from_this()), game_logic);
}

void Ground::on_collision_with(std::shared_ptr<Projectile> projectile, GameLogic& game_logic) {
    projectile->on_collision_with(std::dynamic_pointer_cast<Ground>(shared_from_this()), game_logic);
}