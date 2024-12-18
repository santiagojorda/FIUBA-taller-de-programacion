#ifndef DRAWER_BOX_H
#define DRAWER_BOX_H

#include <map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "../config/game_config.h"
#include "../game_state/elements.h"
#include "../textures/texture_provider.h"

#include "drawable.h"

class DrawerBox: public Drawable {
private:
public:
    DrawerBox(SDL2pp::Renderer& renderer, uint8_t texture_id,
              std::map<std::string, Animation>& animations);

    void draw(const box_t& box);
};

#endif  // DRAWER_BOX_H
