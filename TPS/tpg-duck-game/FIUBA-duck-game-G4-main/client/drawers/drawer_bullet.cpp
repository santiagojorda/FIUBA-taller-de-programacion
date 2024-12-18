#include "drawer_bullet.h"

DrawerBullet::DrawerBullet(SDL2pp::Renderer& renderer, uint8_t texture_id,
                           std::map<std::string, Animation>& animations):
        Drawable(renderer, animations) {
    // tipo de bala, la clave del yaml, por ahora solo hay 1 tipo de bala.
    this->type_animation =
            texture_provider.get_textures_bullet(static_cast<BulletTexture>(texture_id));
    std::string path = this->animations[this->type_animation].get_path();
    this->texture.emplace(renderer, DATA_PATH + path);
}

void DrawerBullet::draw(const bullet_t& bullet) {
    auto config = this->animations.at(this->type_animation).get_config_screen();
    this->flip = static_cast<Direction>(bullet.direction) == Direction::LEFT;
    this->coordenada_x = bullet.bullet.coordinate.get_x();
    this->coordenada_y = bullet.bullet.coordinate.get_y();
    this->scale_width = config.scale_width;
    this->scale_height = config.scale_height;
    this->render();
}
