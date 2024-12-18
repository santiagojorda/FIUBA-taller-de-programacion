#include "server_receiver.h"

#include <string>

Receiver::Receiver(Monitor& monitor, ServerProtocol& protocol):
        monitor(monitor), protocol(protocol) {}

void Receiver::run() {

    // uint16_t action_bytes;

    try {
        uint8_t box_id;
        std::string player_name;
        while (is_running) {
            // modularizar
            protocol.receive_message_picked_up_box(player_name, box_id);
            Command new_command(player_name, box_id);
            monitor.push_command(new_command);
        }
        kill();
    } catch (...) {
        // std::cout << "Se murio el cliente: " << player_name << " - " << e.what() << std::endl;
        kill();
    }
}

bool Receiver::running_status() { return is_running; }

void Receiver::kill() {

    if (is_running) {
        // std::cout << "se cierra receiver" << std::endl;
        is_running = false;
        protocol.kill();
    }
}
