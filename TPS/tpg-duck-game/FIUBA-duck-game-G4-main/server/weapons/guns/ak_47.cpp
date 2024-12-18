#include "ak_47.h"

#include "../projectiles/bullet.h"


gun_config ak_config = {WeaponTextureID::AK_47,  30, ShootingRecoil::SHORT,
                        ProjectileRange::MEDIUM, 1,  5};

AK47::AK47(const Coordinate& _coordinate): Gun(ak_config, _coordinate) {}

void AK47::trigger(ListProjectiles& projectiles, const uint8_t& player_id) {

    this->dispersion++;
    this->dispersion = this->dispersion > 60 ? 49 : this->dispersion;

    int dispersion_y = this->dispersion % 2 ? -1 : 1;

    for (int i = 0; i < ak_config.count_projectiles_x_shoot; i++) {

        if (this->ammo > 0 && this->delay_counter()) {
            projectiles.push_back(std::make_shared<Bullet>(
                    this->projectile_range, this->get_coordinate(), this->get_direction(),
                    this->dispersion * dispersion_y, player_id));
            this->ammo--;
        }
    }
}

void AK47::trigger_out(ListProjectiles& projectiles, const uint8_t& player_id, bool& was_dropped) {
    this->dispersion = 0;
    Gun::trigger_out(projectiles, player_id, was_dropped);
}

AK47::~AK47() {}
