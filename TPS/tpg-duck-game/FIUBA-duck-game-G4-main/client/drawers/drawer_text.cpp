#include "drawer_text.h"


DrawerText::DrawerText(): font(DATA_PATH "/fonts/FreePixel.ttf", 64) {}

void DrawerText::draw(SDL2pp::Renderer& renderer, const std::string& text) {

    SDL2pp::Texture text_sprite(renderer,
                                font.RenderText_Blended(text, SDL_Color{255, 0, 255, 255}));

    renderer.Copy(text_sprite, SDL2pp::NullOpt,
                  SDL2pp::Rect(renderer.GetOutputWidth() / 4, renderer.GetOutputHeight() / 3,
                               text_sprite.GetWidth(), text_sprite.GetHeight()));
}


DrawerText::~DrawerText() {}