#include "banana.h"

#include "../../player/player.h"

gun_config banana_config = {WeaponTextureID::BANANA, 1, ShootingRecoil::NONE,
                            ProjectileRange::MEDIUM, 1, 1};

Banana::Banana(const Coordinate& _coordinate): Gun(banana_config, _coordinate) {}

void Banana::trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                         bool& was_dropped) {
    Gun::trigger_out(projectiles, player_id, was_dropped);
    was_dropped = true;
    is_waiting_to_explotion = true;
}

void Banana::on_collision_with(Player& player, GameLogic& game_logic) {

    (void)game_logic;
    player.on_collision_with(std::dynamic_pointer_cast<Equippable>(shared_from_this()), game_logic);

    if (is_waiting_to_explotion) {
        player.slip();
        die();
    }
}

void Banana::handle_equip(Inventory& inventory) {
    if (is_waiting_to_explotion) {
        die();
        return;
    }
    Gun::handle_equip(inventory);
};

Banana::~Banana() {}