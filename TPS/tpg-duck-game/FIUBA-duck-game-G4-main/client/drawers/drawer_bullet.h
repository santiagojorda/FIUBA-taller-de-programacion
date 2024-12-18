#ifndef DRAWER_BULLET_H
#define DRAWER_BULLET_H

#include <map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "../../common/direction.h"
#include "../game_state/elements.h"
#include "../textures/texture_provider.h"

#include "drawable.h"

class DrawerBullet: public Drawable {
private:
public:
    DrawerBullet(SDL2pp::Renderer& renderer, uint8_t texture_id,
                 std::map<std::string, Animation>& animations);

    void draw(const bullet_t& bullet);
};

#endif  // DRAWER_BULLET_H
