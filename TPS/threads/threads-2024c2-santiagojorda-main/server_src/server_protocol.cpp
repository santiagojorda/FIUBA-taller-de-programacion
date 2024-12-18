#include "server_protocol.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

#define BYTE_CLIENT 0x03
#define BYTE_MESSAGE_PICKED_UP_BOX 0x04
#define BYTE_MESSAGE_BOX_APPEARED 0x05
#define BYTE_SERVER 0x06

ServerProtocol::ServerProtocol(Socket& socket): Protocol(std::move(socket)) {}

void ServerProtocol::send_message_box_appeared() {
    send_byte(BYTE_SERVER);
    send_byte(BYTE_MESSAGE_BOX_APPEARED);
}

void ServerProtocol::send_message_picked_up_box(const std::string& player_name,
                                                const uint8_t& reward_id) {
    send_byte(BYTE_SERVER);
    send_byte(BYTE_MESSAGE_PICKED_UP_BOX);
    send_string(player_name);
    send_byte(reward_id);
}

void ServerProtocol::receive_message_picked_up_box(std::string& player_name, uint8_t& box_id) {
    uint8_t client_byte;
    receive_byte(client_byte);
    receive_string(player_name);
    receive_byte(box_id);
}
