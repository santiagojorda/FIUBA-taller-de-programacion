#include "server_game_logic.h"

#include <cstdint>
#include <iostream>
#include <string>

#include "common_duck.h"
#include "common_shop_item.h"
#include "server_protocol.h"

GameLogic::GameLogic(): duck(), shop() {}

Weapon GameLogic::get_primary_weapon() { return duck.get_primary_weapon(); }
Weapon GameLogic::get_secondary_weapon() { return duck.get_secondary_weapon(); }
std::uint8_t GameLogic::duck_has_knife() { return duck.has_equipped_knife(); }

// refactorizar
bool GameLogic::is_primary_weapon_token(uint8_t token) { return (token >= 4 && token <= 6); }
bool GameLogic::is_secondary_weapon_token(uint8_t token) { return (token >= 1 && token <= 3); }
bool GameLogic::is_secondary_ammo_token(uint8_t token) { return token == 7; }
bool GameLogic::is_primary_ammo_token(uint8_t token) { return token == 8; }
bool GameLogic::is_knife_token(uint8_t token) { return token == 9; }

void GameLogic::action(uint8_t token) {

    if (is_primary_weapon_token(token)) {
        duck.set_primary_weapon(shop.buy_weapon(token));
        std::cout << duck.get_primary_weapon().get_name() << std::endl;
    } else if (is_secondary_weapon_token(token)) {
        duck.set_secondary_weapon(shop.buy_weapon(token));
        std::cout << duck.get_secondary_weapon().get_name() << std::endl;
    } else if (is_primary_ammo_token(token)) {
        duck.add_primary_ammo(shop.buy_primary_ammo());
        std::cout << "Primary Ammo: " << int(duck.get_primary_ammo()) << std::endl;
    } else if (is_secondary_ammo_token(token)) {
        duck.add_secondary_ammo(shop.buy_secondary_ammo());
        std::cout << "Secondary Ammo: " << int(duck.get_secondary_ammo()) << std::endl;
    } else if (is_knife_token(token)) {
        duck.toggle_knife();
        if (duck.has_equipped_knife()) {
            std::cout << "Equipped knife" << std::endl;
        } else {
            std::cout << "Knife not equipped" << std::endl;
        }
    }
    return;
}
