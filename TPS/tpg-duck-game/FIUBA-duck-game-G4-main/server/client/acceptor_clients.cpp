#include "acceptor_clients.h"

#include <iostream>
#include <list>

#include "../player/vector_player_id.h"
#include "../protocol/protocol_server.h"

#include "client.h"

#define BYTE_START_GAME 0xFF

AcceptorClients::AcceptorClients(MonitorClients& _monitor, QueueGameState& _queue_gamestate,
                                 QueueEvents& _queue_events, ListPlayersID& _players_id, const char* server_name):
        skt(server_name),
        monitor(_monitor),
        queue_gamestate(_queue_gamestate),
        queue_events(_queue_events),
        players_id(_players_id) {}

void AcceptorClients::listen_new_client() {
    Socket new_skt = skt.accept();

    ProtocolServer protocol(new_skt);

    // chequear si se envia un dummy para inicializar el game y cortar el acceptor

    uint8_t count_players = protocol.receive_count_players();
    // this->monitor.send_count_players(count_players);

    if (count_players == BYTE_START_GAME) {
        this->stop();
        return;
    }

    VectorPlayerID client_players_id;

    for (uint8_t i = 0; i < count_players; i++) {
        uint8_t id = players_id.size();
        // this->monitor.send_new_player(id);
        players_id.emplace_back(id);
        client_players_id.emplace_back(id);
    }

    monitor.add_item(std::move(new_skt), queue_gamestate, queue_events, client_players_id);
}

void AcceptorClients::run() {
    try {
        while (_keep_running) {
            listen_new_client();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    } catch (...) {
        std::cerr << "error en el acceptor client" << '\n';
    }
    stop();
}

void AcceptorClients::stop() { Thread::stop(); }

AcceptorClients::~AcceptorClients() { Thread::~Thread(); }
