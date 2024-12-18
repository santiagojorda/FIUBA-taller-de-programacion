#ifndef DRAWER_EQUIPMENT_H
#define DRAWER_EQUIPMENT_H

#include <map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "../../common/direction.h"
#include "../../common/state_duck.h"
#include "../animation/animation.h"
#include "../animation/animation_loader.h"
#include "../config/game_config.h"
#include "../game_state/player.h"

#include "drawable.h"

class DrawerEquipment: public Drawable {
private:
    void update_animation(const std::string& type_animation);

public:
    DrawerEquipment(SDL2pp::Renderer& renderer, uint8_t texture_id,
                    std::map<std::string, Animation>& animations);

    void draw(const player_t& player, bool frame_change = false);
};

#endif  // DRAWER_EQUIPMENT_H
