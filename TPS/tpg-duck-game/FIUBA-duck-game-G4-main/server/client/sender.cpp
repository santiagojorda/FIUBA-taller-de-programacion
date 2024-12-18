#include "sender.h"


Sender::Sender(Queue<GameState_t>& _queue, ProtocolServer& _protocol):
        queue(std::ref(_queue)), protocol(std::ref(_protocol)) {}


void Sender::run() {
    try {
        while (this->_keep_running) {
            GameState_t actual_estate = this->queue.pop();
            this->protocol.send_game_state(actual_estate);
        }
    } catch (const std::exception& e) {
        std::cerr << "Sender: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "error en el sender" << '\n';
    }
}

void Sender::send(const GameState_t& game_state) { queue.try_push(game_state); }

Sender::~Sender() {}
