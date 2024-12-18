#include "client.h"

#include <list>

Client::Client(Socket&& _skt, QueueGameState& _queue_gamestate, QueueEvents& _queue_events,
               VectorPlayerID& _players_id):
        skt(std::move(_skt)),
        protocol(skt),
        receiver(_queue_events, protocol, _players_id),
        sender(_queue_gamestate, protocol) {

    receiver.start();
    sender.start();
}

void Client::send_gamestate(const GameState_t& game_state) { sender.send(game_state); }

bool Client::is_alive() { return receiver.is_alive() && sender.is_alive(); }

void Client::send_new_player(const uint8_t& sender) { this->protocol.send_new_player(sender); }

void Client::send_count_players(const uint8_t& sender) { this->protocol.send_count_players(sender); }

void Client::shutdown() {
    skt.shutdown(2);
    skt.close();
}

Client::~Client() {
    this->receiver.join();
    this->sender.join();
}
