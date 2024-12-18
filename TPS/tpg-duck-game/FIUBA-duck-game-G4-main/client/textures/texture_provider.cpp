#include "texture_provider.h"

TextureProvider& TextureProvider::get_instance() {
    static TextureProvider instance;
    return instance;
}

TextureProvider::TextureProvider() {
    textures_weapons = {
            {WeaponTextureID::GRANATE, "granate"},
            {WeaponTextureID::BANANA, "banana"},
            {WeaponTextureID::PEW_PEW_LASER, "pew_pew_laser"},
            {WeaponTextureID::LASER_RIFLE, "laser_rifle"},
            {WeaponTextureID::AK_47, "ak_47"},
            {WeaponTextureID::DUELING_GUN, "dueling_gun"},
            {WeaponTextureID::COWBOY_GUN, "cowboy_gun"},
            {WeaponTextureID::MAGNUM, "magnum"},
            {WeaponTextureID::SHOTGUN, "shotgun"},
            {WeaponTextureID::SNIPER, "sniper"},
            {WeaponTextureID::ARMOR, "armor"},
            {WeaponTextureID::HELMET, "helmet"},
    };

    textures_ducks = {
            {TextureDucks::DUCK_YELLOW, DATA_PATH "/DuckGame-YellowDuck.png"},
            {TextureDucks::DUCK_GREY, DATA_PATH "/DuckGame-GreyDuck.png"},
            {TextureDucks::DUCK_ORANGE, DATA_PATH "/DuckGame-OrangeDuck.png"},
            {TextureDucks::DUCK_WHITE, DATA_PATH "/DuckGame-WhiteDuck.png"},
    };

    textures_action_ducks = {
            {DuckStateType::JUMPING, "jumping"},     {DuckStateType::RUNNING, "running"},
            {DuckStateType::CROUCHING, "crouching"}, {DuckStateType::RECOILING, "recoiling"},
            {DuckStateType::FALLING, "falling"},     {DuckStateType::SLIPPING, "slipping"},
            {DuckStateType::PLANNING, "planning"},   {DuckStateType::IDLE, "idle"},
            {DuckStateType::DEAD, "dead"},
    };

    textures_wings_duck = {
            {DuckStateType::JUMPING, "wings_walking_simple"},
            {DuckStateType::RUNNING, "wings_walking_simple"},
            {DuckStateType::CROUCHING, "wings_crouching"},
            {DuckStateType::RECOILING, "wings_walking_simple"},
            {DuckStateType::FALLING, "wings_walking_simple"},
            {DuckStateType::SLIPPING, "wings_walking_simple"},
            {DuckStateType::PLANNING, "wings_planning"},
            {DuckStateType::IDLE, "wings_walking_simple"},
            {DuckStateType::DEAD, "wings_walking_simple"},
    };

    textures_equipment_ducks = {
            {InventoryDuck::HAS_ARMOR, "has_armor"},
            {InventoryDuck::HAS_HELMET, "has_helmet"},
    };

    textures_floor = {{FloorTexture::FLOOR_MAP_1, DATA_PATH "/NatureTileset.png"}};

    textures_boxes = {{BoxTexture::TYPE_BOX, "box_types"}};

    textures_bullets = {{BulletTexture::BULLET_1, "bullet_1"}};
}

const std::string& TextureProvider::get_weapon_texture(WeaponTextureID id) const {
    return textures_weapons.at(id);
}

const std::string& TextureProvider::get_duck_texture(TextureDucks duck) const {
    return textures_ducks.at(duck);
}

const std::string& TextureProvider::get_duck_action_texture(DuckStateType action) const {
    return textures_action_ducks.at(action);
}

const std::string& TextureProvider::get_duck_equipment_texture(InventoryDuck equipment) const {
    return textures_equipment_ducks.at(equipment);
}

const std::string& TextureProvider::get_textures_floor(FloorTexture id) const {
    return textures_floor.at(id);
}

const std::string& TextureProvider::get_textures_box(BoxTexture id) const {
    return textures_boxes.at(id);
}

const std::string& TextureProvider::get_textures_bullet(BulletTexture id) const {
    return textures_bullets.at(id);
}

const std::string& TextureProvider::get_textures_wings(DuckStateType action) const {
    return textures_wings_duck.at(action);
}
