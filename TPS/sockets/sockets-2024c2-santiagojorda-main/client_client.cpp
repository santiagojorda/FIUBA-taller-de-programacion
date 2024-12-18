#include "client_client.h"

#include <iostream>
#include <string>

#define EXIT_KEY 'q'
#define LENGTH_MESSAGE 512
#define EXIT -1

Client::Client(char* hostname, char* servname): protocol(hostname, servname), duck() {}

void Client::shopping() {
    std::string message;
    bool was_closed = false;
    protocol.receive_message(message, was_closed);
    if (was_closed) {
        return;
    }
    print_message(message);

    while (not was_closed) {
        std::getline(std::cin, message);

        // aca podria usar un try catch

        if (message[0] == EXIT_KEY) {
            was_closed = true;
        } else {
            protocol.send_message(message);
            get_status();
        }
    }
    return;
}

void Client::get_status() {
    std::string weapon;
    bool was_closed = false;
    protocol.receive_message(weapon, was_closed);
    int ammo = protocol.receive_byte_message();
    std::cout << "Primary Weapon: " << weapon << " | Ammo: " << ammo << std::endl;

    protocol.receive_message(weapon, was_closed);
    ammo = protocol.receive_byte_message();
    std::cout << "Secondary Weapon: " << weapon << " | Ammo: " << ammo << std::endl;

    uint8_t knife_is_equipped = protocol.receive_byte_message();
    std::cout << "Knife Equipped: " << (knife_is_equipped ? "Yes" : "No") << std::endl << std::endl;
    return;
}

void Client::print_message(const std::string& message) {
    std::cout << message << std::endl;
    return;
}
