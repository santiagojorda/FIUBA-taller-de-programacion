#ifndef ACCEPTOR_GAME_H
#define ACCEPTOR_GAME_H

#include <list>

#include "../../common/socket.h"
#include "../../common/thread.h"
#include "../events/event.h"
#include "../events/queue_events.h"
#include "../game/queue_game_state.h"
#include "../player/list_players_id.h"

#include "monitor_clients.h"


class AcceptorClients: public Thread {
private:
    Socket skt;
    MonitorClients& monitor;
    QueueGameState& queue_gamestate;
    QueueEvents& queue_events;
    ListPlayersID& players_id;

    void create_client();
    void listen_new_client();

public:
    AcceptorClients(MonitorClients& monitor, QueueGameState& _queue_gamestate,
                    QueueEvents& _queue_events, ListPlayersID& _players_id, const char* server_name);
    void run() override;
    void stop() override;
    ~AcceptorClients();
};

#endif
