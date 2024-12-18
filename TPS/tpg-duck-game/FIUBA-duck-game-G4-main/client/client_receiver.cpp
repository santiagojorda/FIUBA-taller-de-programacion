#include "client_receiver.h"
#include "game_state/client_game_state.h"

ClientReceiver::ClientReceiver(ClientProtocol& protocol,
                               Queue<client_game_state_t>& game_state):
        protocol(protocol), game_state(game_state) {}

void ClientReceiver::run() {
    try {
        while (this->is_alive()) {
            client_game_state_t _game_state;
            protocol.receive_game_state(_game_state);
            game_state.push(_game_state);
        }
    } catch (const std::exception& e) {
        this->_is_alive = false;
    } catch (...) {
        std::cerr << "error en el receiver" << '\n';
    }
}

ClientReceiver::~ClientReceiver() {
    if (this->is_alive()) {
        this->join();
    }
}
