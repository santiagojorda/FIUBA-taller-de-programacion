#include "client_protocol.h"

#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include <arpa/inet.h>

#define LENGTH_MESSAGE 512
#define ERROR -1

#define BYTE_CLIENT_MESSAGE 0x03
#define BYTE_MESSAGE_PICKED_UP_BOX 0x04
#define BYTE_MESSAGE_BOX_APPEARED 0x05
#define BYTE_SERVER_MESSAGE 0x06

#define TEXT_BOX_PICKED_UP_BOX "picked up a"
#define TEXT_BOX_APPEARED "A new box has appeared"
#define TEXT_BAD_MESSAGE "Bad action message"

ClientProtocol::ClientProtocol(char* hostname, char* servname): Protocol(hostname, servname) {}

void ClientProtocol::receive_n_messages(const uint8_t& num_messages,
                                        std::vector<std::string>& messages) {

    uint8_t messages_readed = 0;

    while (messages_readed != num_messages) {
        std::string new_message;

        uint8_t first_byte;
        receive_byte(first_byte);

        uint8_t action_byte;
        receive_byte(action_byte);

        if (action_byte == BYTE_MESSAGE_PICKED_UP_BOX) {

            receive_string(new_message);

            uint8_t reward_id;
            receive_byte(reward_id);

            // tengo que pasar de reward_id a reward_name
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


            new_message = new_message + " " + TEXT_BOX_PICKED_UP_BOX + " " + weapon;
        } else if (action_byte == BYTE_MESSAGE_BOX_APPEARED) {
            new_message = TEXT_BOX_APPEARED;
        } else {
            new_message = TEXT_BAD_MESSAGE;
        }
        messages_readed++;
        messages.push_back(new_message);
    }
}

void ClientProtocol::send_message_pickup(const std::string& player_name, const uint8_t& box_id) {
    send_byte(BYTE_CLIENT_MESSAGE);
    send_string(player_name);
    send_byte(box_id);
}
