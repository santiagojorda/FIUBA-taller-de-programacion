#ifndef CLIENT_H
#define CLIENT_H

#include <vector>

#include "../events/queue_events.h"
#include "../game/queue_game_state.h"
#include "../player/vector_player_id.h"

#include "receiver.h"
#include "sender.h"

class Client {
private:
    Socket skt;
    ProtocolServer protocol;
    Receiver receiver;
    Sender sender;

public:
    Client(Socket&& _skt, QueueGameState& _queue_gamestate, QueueEvents& _queue_events,
           VectorPlayerID& _players_id);
    void shutdown();
    void send_gamestate(const GameState_t& game_state);
    void send_new_player(const uint8_t& sender);
    void send_count_players(const uint8_t& sender);
    bool is_alive();
    ~Client();
};

#endif
