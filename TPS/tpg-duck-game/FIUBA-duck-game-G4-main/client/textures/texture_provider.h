#ifndef TEXTURE_PROVIDER_H
#define TEXTURE_PROVIDER_H

#include <map>
#include <string>

#include "../../common/state_duck.h"
#include "../../common/weapons_id.h"

enum class TextureDucks {
    DUCK_YELLOW,
    DUCK_GREY,
    DUCK_ORANGE,
    DUCK_WHITE,
};

enum class InventoryDuck {
    HAS_ARMOR = 1,
    HAS_HELMET,
};

enum class FloorTexture { FLOOR_MAP_1 };

enum class BoxTexture { TYPE_BOX };

enum class BulletTexture { BULLET_1 };

// SINGLETON
class TextureProvider {
private:
    TextureProvider();
    TextureProvider(const TextureProvider&) = delete;
    TextureProvider& operator=(const TextureProvider&) = delete;

    std::map<WeaponTextureID, std::string> textures_weapons;
    std::map<TextureDucks, std::string> textures_ducks;
    std::map<DuckStateType, std::string> textures_action_ducks;
    std::map<InventoryDuck, std::string> textures_equipment_ducks;
    std::map<FloorTexture, std::string> textures_floor;
    std::map<BoxTexture, std::string> textures_boxes;
    std::map<BulletTexture, std::string> textures_bullets;
    std::map<DuckStateType, std::string> textures_wings_duck;

public:
    static TextureProvider& get_instance();

    const std::string& get_weapon_texture(WeaponTextureID id) const;
    const std::string& get_duck_texture(TextureDucks duck) const;
    const std::string& get_duck_action_texture(DuckStateType action) const;
    const std::string& get_duck_equipment_texture(InventoryDuck equipment) const;
    const std::string& get_textures_floor(FloorTexture id) const;
    const std::string& get_textures_box(BoxTexture id) const;
    const std::string& get_textures_bullet(BulletTexture id) const;
    const std::string& get_textures_wings(DuckStateType id) const;
};

#endif  // TEXTURE_PROVIDER_H
