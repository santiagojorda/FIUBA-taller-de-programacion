#include "drawer_equipment.h"

DrawerEquipment::DrawerEquipment(SDL2pp::Renderer& renderer, uint8_t texture_id,
                                 std::map<std::string, Animation>& animations):
        Drawable(renderer, animations) {
    this->type_animation =
            texture_provider.get_duck_equipment_texture(static_cast<InventoryDuck>(texture_id));
    std::string path = this->animations[this->type_animation].get_path();
    this->texture.emplace(renderer, DATA_PATH + path);
}

void DrawerEquipment::draw(const player_t& player, bool frame_change) {
    auto config = this->animations.at(this->type_animation).get_config_screen();
    this->flip = static_cast<Direction>(player.is_looking) == Direction::LEFT;
    this->coordenada_x = this->flip ? player.sprite.coordinate.get_x() + config.offset_left_x :
                                      player.sprite.coordinate.get_x() + config.offset_right_x;
    this->coordenada_y = player.sprite.coordinate.get_y() + config.offset_y;
    this->scale_width = config.scale_width;
    this->scale_height = config.scale_height;
    if (frame_change) {
        this->frame = static_cast<int>(player.frame);
    }

    this->render();
}
