#ifndef SERVER_H
#define SERVER_H

#include <cstdint>
#include <string>

#include "common_duck.h"
#include "server_game_logic.h"
#include "server_protocol.h"

#define START_SHOPPING_MESSAGE "What arya buying?"
#define BUY_KEY 'B'

class Server {
private:
    GameLogic game_logic;
    ServerProtocol protocol;

    void send_first_message();
    int update_status(const std::string& message);
    void send_status();
    void send_knife_message();
    void send_weapon_message(const std::string& weapon_str, uint8_t ammo);

public:
    explicit Server(const char* servname);
    int start_shopping();
};

#endif
