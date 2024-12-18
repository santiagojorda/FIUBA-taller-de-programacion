#ifndef DRAWER_PLAYER_H
#define DRAWER_PLAYER_H

#include <map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "../../common/state_duck.h"
#include "../animation/animation.h"
#include "../animation/animation_loader.h"
#include "../config/game_config.h"
#include "../game_state/player.h"
#include "../textures/texture_provider.h"

#include "drawable.h"
#include "drawer_equipment.h"
#include "drawer_weapon.h"

class DrawerPlayer: public Drawable {
private:
    std::map<std::string, Animation>& animation_weapon;
    std::map<std::string, Animation>& animation_armor;

    void update_weapon(const player_t& _player);

    void update_armor(const player_t& player);

    void update_helmet(const player_t& player);

    void update_wings(DuckStateType type_wing);


public:
    DrawerPlayer(SDL2pp::Renderer& renderer, uint8_t texture_id,
                 std::map<std::string, Animation>& animations,
                 std::map<std::string, Animation>& animation_weapon,
                 std::map<std::string, Animation>& animation_armor);

    void draw(const player_t& player);
};

#endif  // DRAWER_PLAYER_H
