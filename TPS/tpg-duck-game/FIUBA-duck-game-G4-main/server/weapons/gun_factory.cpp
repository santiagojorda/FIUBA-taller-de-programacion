#include "gun_factory.h"

#include "../../common/weapons_id.h"

#include <iostream>

#include "guns/ak_47.h"
#include "guns/banana.h"
#include "guns/cowboy_gun.h"
#include "guns/dueling_gun.h"
#include "guns/granade.h"
#include "guns/laser_rifle.h"
#include "guns/magnum.h"
#include "guns/pew_pew_laser.h"
#include "guns/shotgun.h"
#include "guns/sniper.h"

GunFactory::GunFactory() {
    map_guns[WeaponTextureID::GRANATE]       = [](Coordinate c) { return std::make_shared<Granade>(c); };
    map_guns[WeaponTextureID::BANANA]        = [](Coordinate c) { return std::make_shared<Banana>(c); };
    map_guns[WeaponTextureID::PEW_PEW_LASER] = [](Coordinate c) { return std::make_shared<PewPewLaser>(c); };
    map_guns[WeaponTextureID::LASER_RIFLE]   = [](Coordinate c) { return std::make_shared<LaserRifle>(c); };
    map_guns[WeaponTextureID::AK_47]         = [](Coordinate c) { return std::make_shared<AK47>(c); };
    map_guns[WeaponTextureID::DUELING_GUN]   = [](Coordinate c) { return std::make_shared<DuelingGun>(c); };
    map_guns[WeaponTextureID::COWBOY_GUN]    = [](Coordinate c) { return std::make_shared<CowboyGun>(c); };
    map_guns[WeaponTextureID::MAGNUM]        = [](Coordinate c) { return std::make_shared<Magnum>(c); };
    map_guns[WeaponTextureID::SHOTGUN]       = [](Coordinate c) { return std::make_shared<Shotgun>(c); };
    map_guns[WeaponTextureID::SNIPER]        = [](Coordinate c) { return std::make_shared<Sniper>(c); };
}


std::shared_ptr<Gun> GunFactory::create_gun(const int& id_weapon, const Coordinate& _coordinate) {
    return map_guns[static_cast<WeaponTextureID>(id_weapon)](_coordinate);
}


GunFactory::~GunFactory() {}
