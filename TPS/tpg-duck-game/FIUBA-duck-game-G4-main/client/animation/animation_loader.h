#ifndef ANIMATION_LOADER_H
#define ANIMATION_LOADER_H

#include <map>
#include <string>

#include <yaml-cpp/yaml.h>

#include "animation.h"

class AnimationLoader {
public:
    static void load_animations(const std::string& file_path,
                                std::map<std::string, Animation>& _animations);
};

#endif  // ANIMATION_LOADER_H
