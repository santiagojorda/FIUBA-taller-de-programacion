#include "drawable.h"

std::map<std::string, Animation> Drawable::empty_animations = {};

Drawable::Drawable(SDL2pp::Renderer& renderer, std::map<std::string, Animation>& animations):
        texture_provider(TextureProvider::get_instance()),
        renderer(renderer),
        animations(animations),
        flip(false),
        coordenada_x(0),
        coordenada_y(0),
        scale_width(0),
        scale_height(0),
        frame(0),
        type_animation("") {}

void Drawable::render() {
    auto anim_rect = this->animations[this->type_animation].get_current_frame(this->frame);

    this->renderer.Copy(*texture, anim_rect,
                        SDL2pp::Rect(coordenada_x, coordenada_y, scale_width, scale_height), 0.0,
                        SDL2pp::NullOpt, this->flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Drawable::render_with_rect(int sprite_x, int sprite_y, int sprite_width, int sprite_height) {

    if (this->texture.has_value()) {
        this->renderer.Copy(*texture, SDL2pp::Rect(sprite_x, sprite_y, sprite_width, sprite_height),
                            SDL2pp::Rect(coordenada_x, coordenada_y, scale_width, scale_height));
    } else {
        throw std::runtime_error("Texture is not initialized");
    }
}


Drawable::~Drawable() {}
