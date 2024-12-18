#include "dueling_gun.h"

#include <functional>

#include "../projectiles/bullet.h"

gun_config dueling_config = {WeaponTextureID::DUELING_GUN, 1, ShootingRecoil::NONE,
                             ProjectileRange::VERY_SHORT,  1, 1};

DuelingGun::DuelingGun(const Coordinate& _coordinate): Gun(dueling_config, _coordinate) {}

void DuelingGun::trigger(ListProjectiles& projectiles, const uint8_t& player_id) {

    for (int i = 0; i < dueling_config.count_projectiles_x_shoot; i++) {
        if (this->ammo > 0) {
            projectiles.push_back(std::make_shared<Bullet>(this->projectile_range,
                                                           this->get_coordinate(),
                                                           this->get_direction(), 45, player_id));
            this->ammo--;
        }
    }
}


DuelingGun::~DuelingGun() {}
