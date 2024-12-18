#include "laser_rifle.h"

#include "../projectiles/bullet_bounce.h"


gun_config laser_config = {WeaponTextureID::LASER_RIFLE, 10, ShootingRecoil::NONE,
                           ProjectileRange::VERY_LARGE,  1,  10};


LaserRifle::LaserRifle(const Coordinate& _coordinate): Gun(laser_config, _coordinate) {}

void LaserRifle::trigger(ListProjectiles& projectiles, const uint8_t& player_id) {
    (void)projectiles;
    (void)player_id;

    for (int i = 0; i < laser_config.count_projectiles_x_shoot; i++) {
        if (this->ammo > 0 && this->delay_counter()) {
            projectiles.push_back(
                    std::make_shared<BulletBounce>(this->projectile_range, this->get_coordinate(),
                                                   this->get_direction(), 0, player_id));
            this->ammo--;
        }
    }
}


LaserRifle::~LaserRifle() {}
