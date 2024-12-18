#include "server_command.h"

#include <iostream>

#define SERVER_BIT 0x06

#define BOX_ID_01 0x01
#define BOX_ID_02 0x02
#define BOX_ID_03 0x03
#define BOX_ID_04 0x04

#define REWARD_ID_01 0x10
#define REWARD_ID_02 0x11
#define REWARD_ID_03 0x12
#define REWARD_ID_04 0x13

Command::Command() {}

Command::Command(const std::string& player_name, const uint8_t box_id):
        player_name(player_name), box_id(box_id) {}

Message* Command::execute(GameLogic& game_logic) {

    uint8_t reward_id = game_logic.pick(box_id);

    if (reward_id) {
        Message* message = new PickedUpMessage(player_name, reward_id);
        return message;
    }
    return nullptr;
}
