#include "gun.h"

#include <iostream>


Gun::Gun(const WeaponTextureID& _texture_id, const uint8_t& _max_ammo,
         const ShootingRecoil& _recoil, const ProjectileRange& _projectile_range,
         const Coordinate& _coordinate, uint8_t _delay_shoot):
        Equippable((uint8_t)_texture_id, _coordinate),
        Directionable(Direction::RIGHT),
        max_ammo(_max_ammo),
        ammo(_max_ammo),
        dispersion(INITIAL_DISPERSION),
        recoil(_recoil),
        projectile_range(_projectile_range),
        delay_counter(_delay_shoot)
        {}

Gun::Gun(const gun_config& _config, const Coordinate& _coordinate) : 
        Equippable((uint8_t)_config.id, _coordinate),
        Directionable(Direction::RIGHT),
        max_ammo(_config.max_ammo),
        ammo(_config.max_ammo),
        dispersion(INITIAL_DISPERSION),
        recoil(_config.recoil),
        projectile_range(_config.range),
        delay_counter(_config.delay_shoot)
        {
                std::cout<< "se creo arma: " << (int)_config.id << std::endl; 

        }


std::shared_ptr<Equippable> Gun::clone() const {
        return std::make_shared<Gun>(*this); 
}

void Gun::handle_equip(Inventory& inventory) { inventory.equip(std::dynamic_pointer_cast<Gun>(shared_from_this())); };

uint8_t Gun::get_max_ammo() { return max_ammo; }

uint8_t Gun::get_ammo() { return ammo; }

void Gun::trigger_out(ListProjectiles& projectiles, const uint8_t& player_id, bool& was_dropped) { 
        (void)projectiles;
        (void)player_id;
        (void)was_dropped;
        this->delay_counter.reset_count(); 
}

void Gun::trigger(ListProjectiles& projectiles, const uint8_t& player_id){
        (void)projectiles;
        (void)player_id;
}

void Gun::handle_explotion(GameLogic& game_logic) { (void)game_logic; }


ShootingRecoil Gun::get_recoil() { return this->recoil; }

Gun::~Gun() {}
