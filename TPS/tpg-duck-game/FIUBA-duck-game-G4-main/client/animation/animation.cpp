#include "animation.h"

// TODO: add sonidos

Animation::Animation(std::string path, const std::vector<frame_t>& frames,
                     config_screen_t config_screen):
        path(path), frames(frames), config_screen(config_screen) {}

// Rect asociado a el sprite en la image
SDL2pp::Rect Animation::get_current_frame(int _frame) const {
    if (_frame < 0 || static_cast<std::size_t>(_frame) >= frames.size()) {
        throw std::out_of_range("Frame index out of range");
    }

    auto& frame = this->frames[_frame];
    return SDL2pp::Rect(frame.x, frame.y, frame.w, frame.h);
}

config_screen_t Animation::get_config_screen() const { return this->config_screen; }

std::string Animation::get_path() const { return this->path; }
