#include "server_message.h"

#include <iostream>

Message::Message() {}

void PickedUpMessage::send(ServerProtocol& protocol) {
    protocol.send_message_picked_up_box(player_name, reward_id);
}

void PickedUpMessage::print() {
    std::string weapon;
    switch (reward_id) {
        case 16:
            weapon = "Bazooka";
            break;
        case 17:
            weapon = "Chainsaw";
            break;
        case 18:
            weapon = "Death ray";
            break;
        case 19:
            weapon = "Shotgun";
            break;
    }


    std::cout << player_name << " picked up a " << weapon << std::endl;
}

void BoxAppearedMessage::send(ServerProtocol& protocol) { protocol.send_message_box_appeared(); }

void BoxAppearedMessage::print() { std::cout << "A new box has appeared" << std::endl; }

PickedUpMessage::PickedUpMessage(const std::string& player_name, const uint8_t reward_id):
        player_name(player_name), reward_id(reward_id) {}
