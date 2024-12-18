#include "client_receiver_lobby.h"

ClientReceiverLobby::ClientReceiverLobby(ClientProtocol& protocol, Queue<game_data_t>& game_data):
        protocol(protocol), game_data(game_data) {}

void ClientReceiverLobby::run() {
    try {
        while (this->is_alive()) {
            game_data_t data;
            protocol.receive_game_data(data);
            game_data.push(data);

            if (data.count_players == 0xFF) {
                this->stop();
            }
        }
        game_data.close();
    } catch (const std::exception& e) {
        this->_is_alive = false;
        game_data.close();
    } catch (...) {
        game_data.close();
        std::cerr << "Error en el receiver del lobby" << std::endl;
    }
}

ClientReceiverLobby::~ClientReceiverLobby() {
    if (this->is_alive()) {
        this->join();
    }
}
