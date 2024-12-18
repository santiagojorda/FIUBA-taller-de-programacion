#include "granade.h"

#define TICK_FOR_EXPLOTION 120  // 30 frames * 4 secodds

#define MAX_RANGE_TILES 1
#include "../../game/game_logic.h"
#define DAMAGE 3
#include "../../player/inventory.h"
#include "../projectiles/bullet.h"
// #include "../projectiles/granade_projectile.h"

#define PLAYER_ID_DUMMY 99
#define NUM_PROJECTILES 10

gun_config granade_config = {WeaponTextureID::GRANATE, 1, ShootingRecoil::NONE,
                             ProjectileRange::MEDIUM,  1, 1};

Granade::Granade(const Coordinate& _coordinate): Gun(granade_config, _coordinate) {}

void Granade::update(GameLogic& game_logic) {
    if (!is_waiting_to_explotion) {
        return;
    }
    tick++;
    if (tick % TICK_FOR_EXPLOTION == 0) {
        game_logic.explote(*this);
        tick = 0;
    }
}

void Granade::trigger(ListProjectiles& projectiles, const uint8_t& player_id) {
    Gun::trigger(projectiles, player_id);
    is_countdown_enabled = true;
}

void Granade::trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                          bool& was_dropped) {
    Gun::trigger_out(projectiles, player_id, was_dropped);
    was_dropped = true;
    is_waiting_to_explotion = true;
}

void Granade::handle_explotion(GameLogic& game_logic) {
    dispersion = 0;

    for (int i = 0; i < NUM_PROJECTILES; i++) {
        Bullet new_bullet(this->projectile_range, get_coordinate(), this->get_direction(),
                          this->dispersion, PLAYER_ID_DUMMY);
        game_logic.add_projectile(std::make_shared<Bullet>(new_bullet));
        dispersion += 360 / NUM_PROJECTILES;
        die();
    }
}

void Granade::handle_equip(Inventory& inventory) {
    if (is_waiting_to_explotion) {
        return;
    }
    Gun::handle_equip(inventory);
};


Granade::~Granade() {}
