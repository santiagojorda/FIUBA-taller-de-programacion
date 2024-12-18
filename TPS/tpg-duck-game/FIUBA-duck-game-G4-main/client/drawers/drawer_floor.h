#ifndef DRAWER_FLOOR_H
#define DRAWER_FLOOR_H

#include <map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "../config/game_config.h"
#include "../game_state/sprite.h"
#include "../textures/texture_provider.h"

#include "drawable.h"

class DrawerFloor: public Drawable {
private:
public:
    DrawerFloor(SDL2pp::Renderer& renderer, uint8_t texture_id);

    void draw(const floor_sprite_t& floor);
};

#endif  // DRAWER_FLOOR_H
