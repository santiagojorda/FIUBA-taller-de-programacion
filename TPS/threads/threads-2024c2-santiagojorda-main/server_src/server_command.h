#ifndef SERVER_COMMAND_H
#define SERVER_COMMAND_H

#include <string>

#include <arpa/inet.h>

#include "server_game_logic.h"
#include "server_message.h"
#include "server_protocol.h"


class Command {
private:
    // cppcheck-suppress unusedStructMember
    std::string player_name;
    // cppcheck-suppress unusedStructMember
    uint8_t box_id;

public:
    Command();
    explicit Command(const std::string& player_name, const uint8_t box_id);
    Message* execute(GameLogic& game_logic);
};

#endif
