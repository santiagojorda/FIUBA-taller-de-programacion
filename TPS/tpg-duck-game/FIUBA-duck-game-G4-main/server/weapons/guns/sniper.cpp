#include "sniper.h"

#include "../projectiles/bullet.h"


gun_config sniper_config{WeaponTextureID::SNIPER, 6, ShootingRecoil::NONE,
                         ProjectileRange::MAX,    1, 20};

Sniper::Sniper(const Coordinate& _coordinate): Gun(sniper_config, _coordinate), blocked(false) {}

void Sniper::trigger(ListProjectiles& projectiles, const uint8_t& player_id) {
    if (!this->blocked) {
        for (int i = 0; i < sniper_config.count_projectiles_x_shoot; i++) {
            if (this->ammo > 0) {
                projectiles.push_back(
                        std::make_shared<Bullet>(this->projectile_range, this->get_coordinate(),
                                                 this->get_direction(), 5, player_id));
                this->ammo--;
            }
        }
        this->blocked = true;
    }
}

void Sniper::trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                         bool& was_dropped) {
    Gun::trigger_out(projectiles, player_id, was_dropped);
    this->blocked = false;
}

Sniper::~Sniper() {}
