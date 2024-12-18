#ifndef DRAWER_WEAPON_H
#define DRAWER_WEAPON_H

#include <map>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "../../common/coordinate.h"
#include "../../common/direction.h"
#include "../animation/animation.h"
#include "../animation/animation_loader.h"
#include "../config/game_config.h"
#include "../game_state/gun.h"

#include "drawable.h"

class DrawerWeapon: public Drawable {
private:
public:
    DrawerWeapon(SDL2pp::Renderer& renderer, uint8_t texture_id,
                 std::map<std::string, Animation>& animations);

    void draw_inventory(const Coordinate& coordinate, uint8_t is_looking);

    void draw(const gun_t& weapon);
};

#endif  // DRAWER_WEAPON_H
