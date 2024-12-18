#include "collidable.h"


void Collidable::on_collision_with(Player& player, GameLogic& game_logic) {
    (void)player;
    (void)game_logic;
}

void Collidable::on_collision_with(std::shared_ptr<Equippable> equip, GameLogic& game_logic) {
    (void)equip;
    (void)game_logic;
}

void Collidable::on_collision_with(std::shared_ptr<Ground> surface, GameLogic& game_logic) {
    (void)surface;
    (void)game_logic;
}

void Collidable::on_collision_with(std::shared_ptr<Projectile> projectile, GameLogic& game_logic) {
    (void)projectile;
    (void)game_logic;
}

void Collidable::on_collision_with(std::shared_ptr<Box> box, GameLogic& game_logic) {
    (void)box;
    (void)game_logic;
}


void Collidable::on_collision_with(std::shared_ptr<Banana> banana, GameLogic& game_logic) {
    (void)banana;
    (void)game_logic;
}
