#ifndef SERVER_GAME_H
#define SERVER_GAME_H

#include <list>

#include "../common_src/common_thread.h"
#include "server_client.h"
#include "server_command.h"
#include "server_game_logic.h"
#include "server_message.h"
#include "server_monitor.h"

#define SLEEP_MILLISECONDS 200

class Game: public Thread {
private:
    GameLogic game_logic;
    Queue<Command>& queue_receiver;

    // cppcheck-suppress unusedStructMember
    std::list<Message*> messages_list;
    Monitor& monitor;
    bool is_running = true;
    void execute_new_commands();
    void print_messages_from_processed_commands();
    void print_messages_if_boxes_available(const uint8_t& count_boxes_appeared);
    void sleep();

public:
    explicit Game(Monitor& monitor);
    void run() override;
    void stop() override;
};

#endif
