#ifndef LOBBY_H
#define LOBBY_H

#include <list>

#include "../client/monitor_clients.h"
#include "../events/queue_events.h"
#include "../game/game.h"
#include "../game/queue_game_state.h"
#include "../player/list_players_id.h"
#include "../../common/thread.h"

class Lobby : public Thread {
private:
    MonitorClients monitor_clients;
    ListPlayersID players_id;
    ListPlayers players;
    QueueEvents queue_events;
    QueueGameState queue_gamestate;
    const char* server_name;
    void init_players();
    void init_game();
    void accept_clients();

public:
    Lobby(const char* _server_name);
    void run() override;
    ~Lobby();
};

#endif
