#include "server_sender.h"

Sender::Sender(Monitor& monitor, ServerProtocol& protocol):
        queue(monitor.new_sender()), protocol(protocol), monitor(monitor) {}


void Sender::run() {
    try {
        while (is_running) {
            Message* message = queue->pop();
            message->send(protocol);
            delete message;
        }
        kill();
    } catch (...) {
        kill();
    }
}

void Sender::kill() {

    if (is_running) {
        is_running = false;
        monitor.clear_queue(queue);
    }
}
