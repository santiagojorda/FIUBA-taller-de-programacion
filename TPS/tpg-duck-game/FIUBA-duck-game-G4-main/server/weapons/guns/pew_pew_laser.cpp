#include "pew_pew_laser.h"

#include "../projectiles/bullet.h"


gun_config pew_pew_laser_config{WeaponTextureID::PEW_PEW_LASER, 12, ShootingRecoil::NONE,
                                ProjectileRange::EXTREME,       3,  10};


PewPewLaser::PewPewLaser(Coordinate _coordinate):
        Gun(pew_pew_laser_config, _coordinate), blocked(false) {}

void PewPewLaser::trigger(ListProjectiles& projectiles, const uint8_t& player_id) {
    if (!this->blocked) {
        if (this->ammo > 0) {
            projectiles.push_back(std::make_shared<Bullet>(this->projectile_range,
                                                           this->get_coordinate(),
                                                           this->get_direction(), 30, player_id));
            projectiles.push_back(std::make_shared<Bullet>(this->projectile_range,
                                                           this->get_coordinate(),
                                                           this->get_direction(), 0, player_id));
            projectiles.push_back(std::make_shared<Bullet>(this->projectile_range,
                                                           this->get_coordinate(),
                                                           this->get_direction(), -30, player_id));
            this->ammo--;
        }
        this->blocked = true;
    }
}


void PewPewLaser::trigger_out(ListProjectiles& projectiles, const uint8_t& player_id,
                              bool& was_dropped) {
    Gun::trigger_out(projectiles, player_id, was_dropped);
    this->blocked = false;
}


PewPewLaser::~PewPewLaser() {}
