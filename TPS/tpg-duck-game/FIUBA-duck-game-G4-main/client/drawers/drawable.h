#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Texture.hh>

#include "../animation/animation.h"
#include "../textures/texture_provider.h"

class Drawable {
protected:
    TextureProvider& texture_provider;
    SDL2pp::Renderer& renderer;
    std::optional<SDL2pp::Texture> texture;
    std::map<std::string, Animation>& animations;
    bool flip;
    int coordenada_x;
    int coordenada_y;
    int scale_width;
    int scale_height;
    int frame;
    std::string type_animation;
    static std::map<std::string, Animation> empty_animations;

public:
    Drawable(SDL2pp::Renderer& renderer, std::map<std::string, Animation>& animations);

    /*Drawable(SDL2pp::Renderer& renderer, SDL2pp::Texture texture,
             std::map<std::string, Animation>& animations);*/

    void render();

    void render_with_rect(int sprite_x, int sprite_y, int sprite_width, int sprite_height);

    // void set_texture(const std::shared_ptr<SDL2pp::Texture>& _texture);

    virtual ~Drawable();
};

#endif  // DRAWABLE_H
