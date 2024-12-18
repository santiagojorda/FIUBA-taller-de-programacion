#include "server_game.h"

#include <chrono>
#include <thread>

#define BOX_ID_01 0x01
#define BOX_ID_02 0x02
#define BOX_ID_03 0x03R
#define BOX_ID_04 0x04

#define REWARD_ID_01 0x10
#define REWARD_ID_02 0x11
#define REWARD_ID_03 0x12
#define REWARD_ID_04 0x13


Game::Game(Monitor& monitor):
        game_logic(), queue_receiver(monitor.get_receiver_queue()), monitor(monitor) {}

void Game::execute_new_commands() {
    Command command;
    while (queue_receiver.try_pop(command)) {
        Message* message = command.execute(game_logic);
        if (message) {
            messages_list.push_back(message->clone());
        }
        delete message;
    }
}

void Game::print_messages_if_boxes_available(const uint8_t& count_boxes_appeared) {
    for (uint8_t i = 0; i < int(count_boxes_appeared); i++) {
        Message* appeared_message = new BoxAppearedMessage();
        appeared_message->print();
        monitor.broadcast(appeared_message);
        delete appeared_message;
    }
}

void Game::print_messages_from_processed_commands() {
    for (Message* msj: messages_list) {
        msj->print();
        monitor.broadcast(msj);
        delete msj;
    }
}

void Game::run() {
    try {
        uint8_t count_boxes_appeared;

        while (is_running) {
            execute_new_commands();
            print_messages_from_processed_commands();
            game_logic.add_iteration(count_boxes_appeared);
            print_messages_if_boxes_available(count_boxes_appeared);
            messages_list.clear();
            sleep();
        }
        stop();
    } catch (...) {
        stop();
    }
}

void Game::sleep() { std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLISECONDS)); }

void Game::stop() { is_running = false; }
