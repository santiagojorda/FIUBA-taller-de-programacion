#include "magnum.h"

#include "../projectiles/bullet.h"

#define MAX_AMMO 6

struct MagnumConfig {
    WeaponTextureID id = WeaponTextureID::MAGNUM;
    uint8_t max_ammo = 6;
    ShootingRecoil recoil = ShootingRecoil::SHORT;
    ProjectileRange range = ProjectileRange::VERY_LARGE;
    uint8_t count_projectiles_x_shoot = 1;
};

gun_config magnum_config = {WeaponTextureID::MAGNUM,     6, ShootingRecoil::SHORT,
                            ProjectileRange::VERY_LARGE, 1, 2};

Magnum::Magnum(const Coordinate& _coordinate): Gun(magnum_config, _coordinate), blocked(false) {}

void Magnum::trigger(ListProjectiles& projectiles, const uint8_t& player_id) {
    if (!this->blocked) {
        for (int i = 0; i < magnum_config.count_projectiles_x_shoot; i++) {
            if (this->ammo > 0) {
                int dispersion_y = this->ammo % 2 ? -1 : 1;
                projectiles.push_back(std::make_shared<Bullet>(
                        this->projectile_range, this->get_coordinate(), this->get_direction(),
                        10 * dispersion_y, player_id));
                this->ammo--;
            }
        }
        this->blocked = true;
    }
}

void Magnum::trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                         bool& was_dropped) {
    Gun::trigger_out(projectiles, player_id, was_dropped);
    this->blocked = false;
}

Magnum::~Magnum() {}
