#ifndef SERVER_GAME_LOGIC_H
#define SERVER_GAME_LOGIC_H

#include <cstdint>
#include <string>

#include "common_duck.h"

class GameLogic {
private:
    Duck duck;
    Shop shop;

    std::string get_str_weapon(uint8_t weapon_no);
    bool is_primary_weapon_token(uint8_t token);
    bool is_secondary_weapon_token(uint8_t token);
    bool is_secondary_ammo_token(uint8_t token);
    bool is_primary_ammo_token(uint8_t token);
    bool is_knife_token(uint8_t token);

public:
    GameLogic();

    Weapon get_primary_weapon();
    Weapon get_secondary_weapon();
    std::uint8_t duck_has_knife();

    void action(uint8_t token);
};

#endif
