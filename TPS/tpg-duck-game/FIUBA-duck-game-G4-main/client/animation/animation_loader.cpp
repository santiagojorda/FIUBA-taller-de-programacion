#include "animation_loader.h"

void AnimationLoader::load_animations(const std::string& file_path,
                                      std::map<std::string, Animation>& _animations) {
    YAML::Node root = YAML::LoadFile(file_path);
    std::map<std::string, Animation> animations;

    for (const auto& state: root) {
        std::string state_name = state.first.as<std::string>();
        std::string path = state.second["texture"].as<std::string>();

        const auto& rects = state.second["rects"];
        std::vector<frame_t> frames;

        for (const auto& rect: rects) {
            frames.push_back(frame_t{rect["x"].as<int>(), rect["y"].as<int>(), rect["w"].as<int>(),
                                     rect["h"].as<int>()});
        }

        int offset_right_x = state.second["offset_right_x"].as<int>();
        int offset_left_x = state.second["offset_left_x"].as<int>();
        int offset_y = state.second["offset_y"].as<int>();
        int scale_width = state.second["scale_width"].as<int>();
        int scale_height = state.second["scale_height"].as<int>();

        animations[state_name] = Animation(path, frames,
                                           config_screen_t{offset_right_x, offset_left_x, offset_y,
                                                           scale_width, scale_height});
    }

    _animations = std::move(animations);
}
