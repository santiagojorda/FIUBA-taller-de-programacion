#include "drawer_weapon.h"

#include "../../common/weapons_id.h"

DrawerWeapon::DrawerWeapon(SDL2pp::Renderer& renderer, uint8_t texture_id,
                           std::map<std::string, Animation>& animations):
        Drawable(renderer, animations) {
    this->type_animation =
            texture_provider.get_weapon_texture(static_cast<WeaponTextureID>(texture_id));
    std::string path = this->animations[this->type_animation].get_path();
    this->texture.emplace(renderer, DATA_PATH + path);
}

void DrawerWeapon::draw(const gun_t& weapon) {
    // this->flip = static_cast<Direction>(is_looking) == Direction::LEFT;
    auto config = this->animations.at(this->type_animation).get_config_screen();
    this->coordenada_x = weapon.sprite.coordinate.get_x();
    this->coordenada_y = weapon.sprite.coordinate.get_y();
    this->scale_width = config.scale_width;
    this->scale_height = config.scale_height;

    // Agrego frame para las bananas y para la granada
    if (static_cast<WeaponTextureID>(weapon.sprite.id_texture) == WeaponTextureID::BANANA ||
        static_cast<WeaponTextureID>(weapon.sprite.id_texture) == WeaponTextureID::GRANATE) {
        this->frame = weapon.frame;
    }

    this->render();
}

void DrawerWeapon::draw_inventory(const Coordinate& coordinate, uint8_t is_looking) {
    auto config = this->animations.at(this->type_animation).get_config_screen();
    this->flip = static_cast<Direction>(is_looking) == Direction::LEFT;
    this->scale_width = config.scale_width;
    this->scale_height = config.scale_height;
    this->coordenada_x = this->flip ? coordinate.get_x() + config.offset_left_x :
                                      coordinate.get_x() + config.offset_right_x;
    this->coordenada_y = coordinate.get_y() + config.offset_y;
    this->render();
}
