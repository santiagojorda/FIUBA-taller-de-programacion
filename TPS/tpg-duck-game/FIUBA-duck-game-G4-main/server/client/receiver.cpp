#include "receiver.h"

Receiver::Receiver(QueueEvents& _queue, ProtocolServer& _protocol,
                   VectorPlayerID& _players_id):
        queue(_queue), protocol(_protocol), players_id(_players_id) {}

void Receiver::init_factories() {
    for (uint8_t& player_id: players_id) {
        this->factories.emplace_back(player_id);
    }
}

void Receiver::push_event(const uint8_t& _player_id, const ActionEvent& _event_id) {
    if (_player_id < factories.size()) {
        std::shared_ptr<Event> event = factories[_player_id].get(_event_id);
        if (event) {
            this->queue.push(event);
        }
    }
}

void Receiver::run() {

    try {
        this->init_factories();
        while (this->_keep_running) {
            uint8_t player_id = 0;
            ActionEvent event_id;
            this->protocol.receive_event(player_id, event_id);
            this->push_event(player_id, event_id);
        }

    } catch (const std::exception& e) {
        std::cerr << "Receiver: " << e.what() << '\n';
    } catch (...) {
        std::cerr << "error en el eceiver" << '\n';
    }
    stop();
}

Receiver::~Receiver() { factories.clear(); }