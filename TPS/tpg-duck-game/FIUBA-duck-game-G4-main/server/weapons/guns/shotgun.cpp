#include "shotgun.h"

#include "../projectiles/bullet.h"


gun_config shotgun_config{WeaponTextureID::SHOTGUN, 2, ShootingRecoil::NONE,
                          ProjectileRange::LARGE,   6, 1};

Shotgun::Shotgun(const Coordinate& _coordinate):
        Gun(shotgun_config, _coordinate), reloaded(false), blocked(false) {}

void Shotgun::trigger(ListProjectiles& projectiles, const uint8_t& player_id) {
    if (blocked)
        return;
    if (this->reloaded) {
        this->reloaded = false;
    } else {
        if (this->ammo > 0) {
            for (int i = 0; i < shotgun_config.count_projectiles_x_shoot; i++) {
                int dispersion_y = i % 2 ? -1 : 1;
                projectiles.push_back(std::make_shared<Bullet>(
                        this->projectile_range, this->get_coordinate(), this->get_direction(),
                        (20 - (i * 5)) * dispersion_y, player_id));
            }
            this->ammo--;
        }
        this->reloaded = true;
    }
    this->blocked = true;
}

void Shotgun::trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                          bool& was_dropped) {
    Gun::trigger_out(projectiles, player_id, was_dropped);
    this->blocked = false;
}
Shotgun::~Shotgun() {}
