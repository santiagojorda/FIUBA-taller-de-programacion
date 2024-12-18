#ifndef GAME_H
#define GAME_H

#include <list>

#include "../../common/thread.h"
#include "../client/monitor_clients.h"
#include "../events/queue_events.h"
#include "list_items_map.h"
#include "../map/map.h"
#include "../player/list_players.h"
#include "../../common/sleep_special.h"
#include "list_boxes.h"
#include "game_logic.h"
#include "queue_game_state.h"
#include "initial_values.h"
#include "round_manager.h"


class Game: public Thread {
private:
    ListPlayers& players;
    Map map;
    ListItemsMap map_items;
    ListProjectiles map_projectiles;
    ListBoxes map_boxes;
    GameLogic game_logic;
    MonitorClients& monitor_client;
    QueueEvents& queue_events; 
    QueueGameState& queue_gamestate;
    RoundManager round_manager;
    inical_values_t inicial_values;
    GameMoment moment = GameMoment::IN_GAME;
    void load_map(const std::string& path_map);

    void reset_values();
    
    void execute_new_events();
    void broadcast_gamestate();

    void display_info(SleepSpecial& sleep);

    GameState_t get_gamestate();

public:
    Game(ListPlayers& _players, MonitorClients& _monitor_client, QueueEvents& _queue_events,
         QueueGameState& _queue_gamestate,  const std::string& path_map);
    void run() override;

    void stop() override;

    ~Game();
};

#endif
