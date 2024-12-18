#ifndef ANIMATION_H
#define ANIMATION_H

#include <string>
#include <vector>

#include <SDL2pp/Rect.hh>

struct frame_t {
    int x, y, w, h;
};

struct config_screen_t {
    int offset_right_x, offset_left_x, offset_y, scale_width, scale_height;
};

class Animation {
protected:
    // path de la texture
    std::string path;
    // vector de frames
    std::vector<frame_t> frames;
    // struct de configuracion para mostrar en pantalla
    config_screen_t config_screen;

public:
    Animation() = default;

    Animation(std::string path, const std::vector<frame_t>& frames, config_screen_t config_screen);

    config_screen_t get_config_screen() const;

    std::string get_path() const;

    SDL2pp::Rect get_current_frame(int frame) const;
};

#endif  // ANIMATION_H
