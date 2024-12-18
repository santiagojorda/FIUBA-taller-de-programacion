#include "client_sender.h"

ClientSender::ClientSender(ClientProtocol& protocol, Queue<ClientEvent_t>& commands):
        protocol(protocol), commands(commands) {}


void ClientSender::run() {
    try {
        while (this->is_alive()) {
            // if (this->protocol.is_closed()) {}
            ClientEvent_t message_to_send = this->commands.pop();
            this->protocol.send_action(message_to_send.id_player, message_to_send.action);
        }
    } catch (const ClosedQueue& e) {
        this->_is_alive = false;
    } catch (const std::exception& e) {
        this->_is_alive = false;
          std::cerr << "unexpected error in Sender" << std::endl;
    }
}

ClientSender::~ClientSender() {
    if (this->is_alive()) {
        this->join();
    }
}
