#include "server_server.h"

#include <iostream>
#include <string>

#include "common_shop_item.h"
#include "server_game_logic.h"

#define EXIT -1

Server::Server(const char* servname): game_logic(), protocol(servname) {}

int Server::start_shopping() {
    bool was_closed = false;
    send_first_message();

    std::string message;
    while (not was_closed) {
        protocol.receive_message(message, was_closed);
        if (was_closed) {
            break;
        }

        int status = update_status(message);
        if (status == EXIT) {
            break;
        } else {
            send_status();
        }
    }

    return 0;
}

int Server::update_status(const std::string& message) {

    char action = message[0];

    if (action != BUY_KEY)
        return 0;

    for (int i = 1; i < int(message.length()); i++) {
        int digit = message[i] - '0';
        game_logic.action(digit);
    }

    return 0;
}

void Server::send_status() {
    std::string weapon_str;
    uint8_t ammo;

    weapon_str = game_logic.get_primary_weapon().get_name();
    ammo = game_logic.get_primary_weapon().get_ammo();
    send_weapon_message(weapon_str, ammo);

    weapon_str = game_logic.get_secondary_weapon().get_name();
    ammo = game_logic.get_secondary_weapon().get_ammo();
    send_weapon_message(weapon_str, ammo);

    send_knife_message();
}


void Server::send_first_message() {
    std::string first_message(START_SHOPPING_MESSAGE);
    protocol.send_message(first_message);
    return;
}

void Server::send_weapon_message(const std::string& weapon_str, uint8_t ammo) {
    protocol.send_message(weapon_str);
    protocol.send_byte_message(ammo);
    return;
}

void Server::send_knife_message() {
    protocol.send_byte_message(game_logic.duck_has_knife());
    return;
}
