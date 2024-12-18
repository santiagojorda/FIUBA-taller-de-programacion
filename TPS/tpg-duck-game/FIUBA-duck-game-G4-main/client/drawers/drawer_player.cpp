#include "drawer_player.h"

#include <map>

#include "../../common/direction.h"
#include "../../common/weapons_id.h"
#include "../game_state/player.h"

DrawerPlayer::DrawerPlayer(SDL2pp::Renderer& renderer, uint8_t texture_id,
                           std::map<std::string, Animation>& animations,
                           std::map<std::string, Animation>& animation_weapon,
                           std::map<std::string, Animation>& animation_armor):
        Drawable(renderer, animations),
        animation_weapon(animation_weapon),
        animation_armor(animation_armor) {
    std::string path =
            this->texture_provider.get_duck_texture(static_cast<TextureDucks>(texture_id));
    this->texture.emplace(renderer, path);
}

void DrawerPlayer::draw(const player_t& player) {
    this->flip = static_cast<Direction>(player.is_looking) == Direction::LEFT;
    this->coordenada_x = player.sprite.coordinate.get_x();
    this->coordenada_y = player.sprite.coordinate.get_y();
    this->scale_height = TILE_SIZE;
    this->scale_width = TILE_SIZE;
    try {
        this->frame = static_cast<int>(player.frame);
        this->type_animation =
                texture_provider.get_duck_action_texture(static_cast<DuckStateType>(player.state));
        this->render();
    } catch (...) {
        std::cerr << "No hay textura del estado: " << (uint8_t)player.state << std::endl;
    }
    if (static_cast<int>(player.inventory.helmet) != 0) {
        this->update_helmet(player);
    }

    if (static_cast<int>(player.inventory.armor) != 0) {
        this->update_armor(player);
    }

    if (static_cast<int>(player.inventory.weapon) != 0) {
        this->frame = static_cast<int>(player.frame);
        this->update_weapon(player);
    }


    update_wings(static_cast<DuckStateType>(player.state));
}

void DrawerPlayer::update_weapon(const player_t& player) {
    DrawerWeapon drawer_weapon(this->renderer, player.inventory.weapon, this->animation_weapon);
    drawer_weapon.draw_inventory(player.sprite.coordinate, player.is_looking);
}


void DrawerPlayer::update_armor(const player_t& player) {
    uint8_t valor = 1;
    DrawerEquipment drawer_equipment(this->renderer, valor, this->animation_armor);
    drawer_equipment.draw(player);
}

void DrawerPlayer::update_helmet(const player_t& player) {
    uint8_t valor = 2;
    DrawerEquipment drawer_equipment(this->renderer, valor, this->animation_armor);
    drawer_equipment.draw(player);
}

void DrawerPlayer::update_wings(DuckStateType duck_status) {
    if (duck_status == DuckStateType::DEAD) {
        return;
    }


    this->type_animation = texture_provider.get_textures_wings(duck_status);
    auto config = this->animations.at(this->type_animation).get_config_screen();
    this->scale_height = config.scale_height;
    this->scale_width = config.scale_width;
    this->coordenada_x += flip ? config.offset_left_x : config.offset_right_x;
    this->coordenada_y += config.offset_y;
    this->render();
}
