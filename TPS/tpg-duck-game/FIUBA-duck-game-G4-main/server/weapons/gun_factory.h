#ifndef GUN_FACTORY_H
#define GUN_FACTORY_H

#include <map>
#include <memory>
#include "gun.h"
#include <functional>

class GunFactory {
private:
    std::map<WeaponTextureID, std::function<std::shared_ptr<Gun>(Coordinate)>> map_guns;
public:
    GunFactory();

    std::shared_ptr<Gun> create_gun(const int& id_weapon, const Coordinate& _coordinate);

    ~GunFactory();
};


#endif  // GUN_FACTORY_H
